import argparse
import json
import os
import pathlib
import textwrap
import traceback

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

parser.add_argument('--full', default=False, action='store_true',
                    help='When passed, existing header files are regenerated instead of the default behavior of being skipped.')

parser.add_argument('--debug', required=False,
                    help='Does not work when --single is given. When going through files in a folder, limit processing to this EPD JSON file. Used for debugging.', default=None)

args = parser.parse_args()

jsonpath = args.jsonpath
output = args.output
singleMode = args.single
verbose = args.verbose
fullMode = args.full
debug = args.debug

if singleMode and debug is not None:
    print('Cannot use both --single and --debug')
    exit(1)
elif debug is not None:
    verbose = True

# * Validate passed in jsonpath
# ******************************

path = pathlib.Path(jsonpath)
outpath = pathlib.Path(output)

if not path.exists():
    print(f'Given jsonpath \'{jsonpath}\' does not exist')
    exit(1)

if singleMode and path.is_dir():
    print(f'Given jsonpath is a directory, expected it to be a file (Note: this is because --single flag was passed)')
    exit(1)
elif not singleMode and path.is_file():
    print(f'Given jsonpath is a file, expected it to be a directory (Note: use the --single flag to parse single files)')
    exit(1)

if not outpath.exists():
    print(f'Given output path does not exist')
    exit(1)
elif not outpath.is_dir():
    print(f'Given output path is not a directory')
    exit(1)


def ProcessFile(path: pathlib.Path, log: Logger):
    log.info(f'Parsing file: {path.name}...')

    f = open(path)
    data = json.load(f)
    f.close()

    det = EPaperDetails(path.name)
    det.parseFromJson(data)

    mode = det.DetermineMode()
    result: str = ''

    try:
        if mode == 'Black1BitEPD':
            log.info('Determined display type to be Black1BitEPD')
            result = generators.Black1BitEPD_Generator(
                det, log).BuildHeaderfile()
        elif mode == 'Black2BitEPD':
            log.info('Determined display type to be Black2BitEPD')
            result = generators.Black2BitEPD_Generator(
                det, log).BuildHeaderfile()
        elif mode == 'RedBlack1BitEPD':
            log.info('Determined display type to be RedBlack1BitEPD')
            result = generators.RedBlack1BitEPD_Generator(
                det, log).BuildHeaderfile()
        elif mode == 'Color2BitEPD':
            log.info('Determined display type to be Color2BitEPD')
            result = generators.Color2BitEPD_Generator(
                det, log).BuildHeaderfile()
        elif mode == '6Color4BitEPD':
            log.info('Determined display type to be 6Color4BitEPD')
            result = generators._6Color4BitEPD_Generator(
                det, log).BuildHeaderfile()
        elif mode == '7Color4BitEPD':
            log.info('Determined display type to be 7Color4BitEPD')
            result = generators._7Color4BitEPD_Generator(
                det, log).BuildHeaderfile()
        elif mode == 'UnknownSingleChannel':
            log.warning(
                f'The JSON parser was unable to determine the display type. it\'s best guess is \'UnknownSingleChannel\' colorchannels = ({",".join(det.supportColorChannels)})')
            log.warning(
                "but you'll have to figure this out manually. Skipping file.")
        elif 'unknown' in mode.lower():
            log.warning(
                f'The JSON parser was unable to determine the display type ({mode}). Skipping file.')
        elif mode == 'NoExampleFile':
            log.error(
                f"No example file. Skipping file as I don't know how to deal with it.")
        else:
            log.error(
                det, f'Critical Error! "{mode}" returned by EpaperDetails.DetermineMode()! This should never occur!')
    except:
        log.error(f'Error while processing {det.filename}...')
        log.error('------ see traceback below -----\n')
        log.error(traceback.format_exc())
        log.error('')
        print()

    det.mode = mode

    if result != '':
        f = open(outpath / f'{det.name}.h', 'w')
        f.write(result)
        f.close()
        return det, True

    return det, False


def GenerateSourceFile(det: EPaperDetails):
    """
    Given a JSON generate a C++ source file (thankfully this is much easier than generating a headerfile)
    """
    code = f"""extern "C" {{
namespace epaperapi::devices::{det.name}::controller {{
#include "../epaper/e-Paper/{det.name}.c"
}} // namespace epaperapi::devices::{det.name}::controller
}}
"""
    f = open(outpath / f'{det.name}.cpp', 'w')
    f.write(code)
    f.close()


if singleMode:
    log = Logger(verbose, path.name)
    ProcessFile(path, log)
elif debug is not None:
    if fullMode:
        print('Warning: --full ignored when running with --debug.')

        file_path: pathlib.Path = path / debug
        log = Logger(verbose, pathlib.Path(file_path).name)

        if not file_path.exists():
            log.error(f'{file_path} does not exist in {path}')
            exit(1)

        det, status = ProcessFile(file_path, log)

        if status == True:
            GenerateSourceFile(det)
            log.info(
                f'Successfully processed {file_path} and created header & source files')
        else:
            log.error(f'Failed to process {file_path}')
else:
    # loop through json files in the directory and generate files
    totalCount = 0
    existingCount = 0
    processed: list[EPaperDetails] = []
    failed: list[EPaperDetails] = []
    for file_path in path.rglob('*.json'):
        totalCount += 1
        log = Logger(verbose, pathlib.Path(file_path).name)

        if not fullMode and os.path.exists(outpath / f'{file_path.stem}.h'):
            log.info(
                f"Skipping {str(file_path)} as a header file for it ({str(outpath / f'{file_path.stem}.h')}) already exists.")
            existingCount += 1
            continue

        det, status = ProcessFile(file_path, log)
        if status == True:
            processed.append(det)
            GenerateSourceFile(det)
        else:
            failed.append(det)

    print()
    print('-------------------')
    print(
        f'Processed {len(processed)} JSON files and generated header files for them')
    print(f'{totalCount - len(processed)} out of the discovered {totalCount} JSON files were skipped\n')

    if verbose:
        print(
            f'Of these skipped, {existingCount} were skipped because a header file for them already existed.')
    else:
        print(
            f'Of these skipped, {existingCount} were skipped because a header file for them already existed.  Rerun with --verbose to see exactly which ones.')

    print('-------------------')
    print('The following EPD JSON files were skipped:\n')
    for i in failed:
        log = f'[{i.filename}]'
        contents = f'Full Name={i.fullName}\nMode={i.mode}\nColors={",".join(i.supportColorChannels)}\n'
        contents += f'BitmapFunction={i.bitmapFunction}\nPaintScale={i.paintScale}'

        contents = textwrap.indent(contents, '  ')

        print(log)
        print(contents)
        print()

print('\nGenerate.py Done!')
