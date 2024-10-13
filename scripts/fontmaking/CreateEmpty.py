"""
This script creates a directory full of empty images so a custom font not based on an existing one can be created.
"""

from pathlib import Path
import string
import common
import argparse
import json
import os

common.requirePackages(["PIL"])

# autopep8: off
from PIL import Image
from PIL import ImageFont
from PIL import ImageDraw
# autopep8: on

parser = argparse.ArgumentParser(
    prog='CreateEmpty.py',
    description='Generates empty images for manual creation of a font and can later be turned into a C++ font headerfile',
)

parser.add_argument("fontname", help="Name of the font")
parser.add_argument("width", help="Width of generated images")
parser.add_argument("height", help="Height of generated images")
parser.add_argument("--charset", required=False,
                    help='Path to file containing character set. Default is used if none provided.')

args = parser.parse_args()
charset: str = '' if args.charset else string.digits + \
    string.ascii_letters + string.punctuation + ' '
fontname = args.fontname
size = int(args.height)

width = int(args.width)
height = int(args.height)

if charset == '':
    # read from file
    cfile = open(args.charset, 'r')
    charset = cfile.readline()
    cfile.close()

print(
    f"Generating {len(charset)} images {width}px X {height}px...")
print(f"Character Set: {charset}")

dir = f'./{fontname}_{size}px/'
os.makedirs(dir)

i = 0
# store filenames and what character they represent as well as other important information about the font
config = {
    "name": args.fontname,
    "fontsize": int(size),
    "charset": charset
}
for char in charset:
    img = Image.new('1', (width, height), 1)
    fname = f'char_{i}' + '.bmp'
    config[char] = fname
    img.save(dir + fname)
    i += 1

    print(f'\tGenerated {dir + fname}')

# create config file to map characters to
cnfgFile = open(dir + 'config.json', 'w')
json.dump(config, cnfgFile, indent=4)
cnfgFile.close()

print(
    f'\tCreated config file {dir}config.json with {i} characters')
print('\tDone!')
