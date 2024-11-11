import argparse
import json
import pathlib

import common
import helpers.generators as generators
from helpers.ClassBuilder import DrawTargetClassBuilder
from helpers.logging import Logger

common.requirePackages(["openai|openai", "alive_progress|alive-progress"])

# autopep8: off
from helpers.EPaperDetails import EPaperDetails
# autopep8: on

# * Parse CLI Arguments
# **********************

parser = argparse.ArgumentParser(
    prog='Generate.py',
    description='Using JSON generated from Parse.py generates C++ DrawTarget code files'
)

parser.add_argument('jsonpath', help='Path to directory containing JSON files')

parser.add_argument(
    'output', help='Path to directory output resulting code files')

parser.add_argument(
    '--single', help='Process a single JSON file rather than a directory', action='store_true', default=False)

parser.add_argument(
    '--verbose', help='Print all debug messages', action='store_true', default=False
)

args = parser.parse_args()

jsonpath = args.jsonpath
singleMode = args.single
verbose = args.verbose

# * Validate passed in jsonpath
# ******************************

path = pathlib.Path(jsonpath)

if not path.exists():
    print(f'Given jsonpath \'{jsonpath}\' does not exist')
    exit(1)

if singleMode and path.is_dir():
    print(f'Given jsonpath is a directory, expected it to be a file (Note: this is because --single flag was passed)')
    exit(1)
elif not singleMode and path.is_file():
    print(f'Given jsonpath is a file, expected it to be a directory (Note: use the --single flag to parse single files)')
    exit(1)


def logParse(det: EPaperDetails, message):
    print(f'[{det.filename}]: {message}')


if singleMode:
    print(f'Parsing single file: {path.name}...')
    data = json.load(open(path))

    det = EPaperDetails(path.name)
    det.parseFromJson(data)

    mode = det.DetermineMode()
    result: str

    log = Logger(verbose, det.filename)

    if mode == 'Black1BitEPD':
        result = generators.Black1BitEPD_Generator(det, log).BuildHeaderfile()
    elif mode == 'RedBlack1BitEPD':
        # todo implement
        logParse(det, 'Mode detected as RedBlack1BitEPD but not implemented yet!')
        pass
    elif mode == 'UnknownSingleChannel':
        logParse(
            det, f'Unknown display type, best guess is \'UnknownSingleChannel\' colorchannels = ({",".join(det.supportColorChannels)})')
    elif mode == 'Unknown':
        logParse(det, 'Unknown display type')
    else:
        logParse(
            det, 'Critical Error! No mode returned by EpaperDetails.DetermineMode()!')

    if result != '':
        f = open(f'{det.name}.h', 'w')
        f.write(result)
        f.close()

else:
    print('Only singlemode parsing is supported at the moment...')
