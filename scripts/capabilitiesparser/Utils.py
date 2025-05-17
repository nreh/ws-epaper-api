import argparse
import json
import os
import pathlib
import shutil
import traceback
import csv

from helpers import logging
from helpers.EPaperDetails import EPaperDetails

# * Parse CLI Arguments
# **********************

parser = argparse.ArgumentParser(
    prog='Utils.py',
    description='Script for performing useful actions'
)

group = parser.add_mutually_exclusive_group(required=True)

group.add_argument(
    '--categorize', help='Given a directory containing parsed capabilities, copy them to a categorized directory by display type.')

group.add_argument(
    '--table', help='Given a directory containing parsed capabilities, generate a table describing it.')

args = parser.parse_args()

categorize = args.categorize
table = args.table

if categorize is not None:
    print("Running 'categorize' utility...")

    categorize = pathlib.Path(categorize)

    if not categorize.exists():
        print('Passed path does not exist')
        exit(1)

    if not categorize.is_dir():
        print('Passed path must a directory containing .json files')
        exit(1)

    # first create a directory where the categorized .json will be moved to
    OUTPUT_DIRECTORY_NAME = './ignore_Utils_categorize'
    os.mkdir(OUTPUT_DIRECTORY_NAME)
    outputdir = pathlib.Path(OUTPUT_DIRECTORY_NAME)

    # now go through each .json file and copy it to the categorized directory

    totalCount = 0
    existingCount = 0
    processed: list[str] = []
    failed: list[str] = []
    for file_path in categorize.rglob('*.json'):
        totalCount += 1
        log = logging.Logger(True, pathlib.Path(file_path).name)

        log.info(f'Parsing file {file_path}...')

        try:
            f = open(file_path)
            data = json.load(f)
            f.close()

            det = EPaperDetails(file_path.name)
            det.parseFromJson(data)

            mode = det.DetermineMode()

            # create a directory for this mode if it doesn't already exist:
            cdir = outputdir / pathlib.Path(mode)
            if not cdir.exists():
                os.mkdir(cdir)

            # copy to the category directory
            shutil.copy(file_path, cdir)

            log.info(f'Categorized as {mode}')

            processed.append(file_path.name)
        except:
            log.error(f'Error while processing {file_path}...')
            log.error('------ see traceback below -----\n')
            log.error(traceback.format_exc())
            log.error('')
            print()

            failed.append(file_path.name)

    print(
        f'\n\nDONE! Processed {totalCount} files of which {len(failed)} failed')

    if len(failed) > 0:
        print('\nThe following files failed to process:\n')
        for i in failed:
            print(f' * {i}')
            print()

elif table is not None:
    print("Running 'table' utility...")

    table = pathlib.Path(table)

    if not table.exists():
        print('Passed path does not exist')
        exit(1)

    if not table.is_dir():
        print('Passed path must a directory containing .json files')
        exit(1)

        # first create a directory where the categorized .json will be moved to
    OUTPUT_DIRECTORY_NAME = './ignore_Utils_table/'
    os.mkdir(OUTPUT_DIRECTORY_NAME)
    outputdir = pathlib.Path(OUTPUT_DIRECTORY_NAME)

    displays = open(outputdir/'supportedDisplays.csv', 'w')
    displaysCSV = csv.writer(displays)

    displaysCSV.writerow(['Display Name', 'Headerfile', 'Width', 'Height',
                         'Type', 'Supported Colors', 'Supported?'])

    # now go through each .json file

    totalCount = 0
    existingCount = 0
    processed: list[str] = []
    failed: list[str] = []
    for file_path in table.rglob('*.json'):
        totalCount += 1
        log = logging.Logger(True, pathlib.Path(file_path).name)

        log.info(f'Parsing file {file_path}...')

        try:
            f = open(file_path)
            data = json.load(f)
            f.close()

            det = EPaperDetails(file_path.name)
            det.parseFromJson(data)

            mode = det.DetermineMode()

            supported = 'Yes' if mode != 'Unknown' else 'No'
            displaysCSV.writerow(
                [det.fullName, f'{det.name}.h', det.screenWidth, det.screenHeight, mode, det.supportColorChannels, supported])

            processed.append(file_path.name)
        except:
            log.error(f'Error while processing {file_path}...')
            log.error('------ see traceback below -----\n')
            log.error(traceback.format_exc())
            log.error('')
            print()

            failed.append(file_path.name)

    print(
        f'\n\nDONE! Processed {totalCount} files of which {len(failed)} failed')

    if len(failed) > 0:
        print('\nThe following files failed to process:\n')
        for i in failed:
            print(f' * {i}')
            print()


else:
    print('Error: Unexpected arguments, not utility specified')
    exit(1)

print('\n---\nUtils.py script completed.')
