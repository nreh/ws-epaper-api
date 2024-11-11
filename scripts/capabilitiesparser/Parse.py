# This script goes through header files and generates DrawTargets classes for each. It uses ChatGPT to determine
# capablities and other details because I'm too lazy to go through all of them manually :P

import textwrap
import traceback
import common
import os
import argparse
import pathlib

common.requirePackages(["openai|openai", "alive_progress|alive-progress"])

# autopep8: off
from openai import OpenAI
from alive_progress import alive_bar
from helpers.EPaperDetails import EPaperDetails, SetUpOpenAI
# autopep8: on

# * Parse CLI Arguments
# **********************

parser = argparse.ArgumentParser(
    prog='Parse.py',
    description='Parses header and test files using ChatGPT and records functions, capabilities, and other information.'
)

parser.add_argument('headerpath',
                    help='Path to directory containing header files')
parser.add_argument(
    'examplepath', help='Path to directory containing .c example files')
parser.add_argument(
    '--single', help='When this flag is used, you can pass in a single file instead of a directory for headerpath and examplepath',
    action='store_true')
parser.add_argument('--model', default='gpt-4o',
                    help='ChatGPT model to use, default is \'gpt-4o\'', required=False)
parser.add_argument(
    '--prompt', help='Path to file containing prompt given to ChatGPT. Default is \'prompt.txt\'', default='prompt.txt',
    required=False)

parser.add_argument(
    "--output", help='Directory to output parsed results - default is \'./results\'', default='./results')

parser.add_argument('--full',
                    help='By default files that have already been parsed will not be reparsed. If this flag is passed all files regardless of whether they have been parsed or not will be reparsed and have .json files regenerated.', action='store_true', default=False)

args = parser.parse_args()

headerpath = args.headerpath
examplepath = args.examplepath
singlemode = args.single
model = args.model
promptfile = args.prompt
outputdir = args.output
fullMode = args.full

# * Model and prompt file
# ************************

f = open(promptfile, 'r')
prompt = f.read()
f.close()

print('Using the following prompt:')
maxwidth = 100
print('-' * maxwidth)
print(textwrap.fill(prompt, width=maxwidth))
print('-' * maxwidth)
print()

# * Get OpenAPI key
# ******************

OPENAI_API_KEY = os.environ.get('OPENAI_PERSONAL_API_KEY')
EPAPER_DIR = './epaper/e-Paper/'

if OPENAI_API_KEY is None:
    raise RuntimeError(
        "No OPENAI_API_KEY in environment variables! This script uses ChatGPT so please supply the API key.")

# * Validate passed in paths
# ***************************

validationErrorHeader = None
validationErrorExample = None

with pathlib.Path(headerpath) as hp:
    if not hp.exists():
        validationErrorHeader = f"Given headerpath does not exist ({headerpath})!"
    else:
        if singlemode:
            if hp.is_dir():
                validationErrorHeader = f'Given headerpath ({headerpath}) is a directory, expected it be a file. (Note: This is because the --single flag was given)'
        else:
            if hp.is_file():
                validationErrorHeader = f'Given headerpath ({headerpath}) is a file, expected it be a directory. (Note: Use the --single flag to parse single files instead of directories)'

with pathlib.Path(examplepath) as hp:
    if not hp.exists():
        validationErrorExample = f"Given examplepath does not exist ({examplepath})!"
    else:
        if singlemode:
            if hp.is_dir():
                validationErrorExample = f'Given examplepath ({examplepath}) is a directory, expected it be a file. (Note: This is because the --single flag was given)'
        else:
            if hp.is_file():
                validationErrorExample = f'Given examplepath ({examplepath}) is a file, expected it be a directory. (Note: Use the --single flag to parse single files instead of directories)'

if not validationErrorHeader == None or not validationErrorExample == None:
    print(validationErrorHeader)
    print()
    print(validationErrorExample)
    exit(1)

# Make sure output directory exists

if not pathlib.Path(outputdir).exists():
    print(
        f'Output directory {outputdir} does not exist, use the --output flag to set it to a custom directory')
    exit()
elif not pathlib.Path(outputdir).is_dir():
    print(f'{outputdir} is not a directory')
    exit()

print()

# * Set up OpenAI API
# ********************

SetUpOpenAI(OPENAI_API_KEY, prompt, model)
print('Done!')
print()

# * Begin parsing file(s)
# ************************
if singlemode:
    print("Note: Parsing single file since --single flag passed")
    print()
    with alive_bar(bar=None, title=pathlib.Path(headerpath).name, monitor=None) as prog:
        try:
            det = EPaperDetails(pathlib.Path(headerpath).stem)
            det.ParseFromHeaderFile(headerpath)
            det.ParseExampleFile(examplepath)
            det.Save(outputdir)
        except Exception as e:
            function_name = traceback.extract_tb(e.__traceback__)[-1].name
            print(f'[X] {headerpath}: {str(e)} in function {function_name}()')

    print()
    print('--------------------')
    print("Done! Parsed single header and test file")

else:
    # find all header files in the headerpath directory
    headerfiles = [os.path.join(headerpath, f) for f in os.listdir(
        headerpath) if os.path.isfile(os.path.join(headerpath, f)) and f.endswith('.h')]
    print(f'Found {len(headerfiles)} header files in the {headerpath} directory')

    # find all .c source files in the examplepath directory
    examplefiles = [os.path.join(examplepath, f) for f in os.listdir(
        examplepath) if os.path.isfile(os.path.join(examplepath, f)) and f.endswith('.c')]
    print(
        f'Found {len(examplefiles)} header files in the {examplepath} directory')

    if not len(headerfiles) == len(examplefiles):
        print(
            f"Warning, mismatch between number of header files ({len(headerfiles)}) and number of example files ({len(examplefiles)})!")

    print()
    with alive_bar(len(headerfiles), title_length=20) as prog:
        for h in headerfiles:
            name = pathlib.Path(h).stem
            prog.title = name

            if not fullMode and (pathlib.Path(outputdir) / f'{name}.json').exists():
                # don't regenerate existing json
                print(
                    f'[!] Skipping processing of {name}.h due to existing file {name}.json')
            else:
                try:
                    det = EPaperDetails(name)
                    det.ParseFromHeaderFile(h)

                    # find example file
                    examplename = det.filename + '_test.c'
                    exFile = pathlib.Path(examplepath) / examplename

                    if exFile.exists():
                        det.ParseExampleFile(str(exFile))
                    else:
                        print(
                            f"[!] Unable to find example file for {name} (file {examplename} does not exist in example directory)")

                    det.Save(outputdir)
                except Exception as e:
                    function_name = traceback.extract_tb(
                        e.__traceback__)[-1].name
                    print(
                        f'[X] {name}.h: {str(e)} in function {function_name}()')
            prog()
