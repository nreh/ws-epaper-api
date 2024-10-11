"""
This script aids in the creation of fonts by generating images of characters that can be later used to generate font header
files by the 'Images2FontHeaders.py' script.
"""

import common
import argparse
import string
import io
import os
import json
from pathlib import Path

common.requirePackages(["PIL"])

# autopep8: off
from PIL import Image
from PIL import ImageFont
from PIL import ImageDraw
# autopep8: on

parser = argparse.ArgumentParser(
    prog='Font2Images.py',
    description='Generates images from a .ttf file that can be manually editted and later turned into a C++ font headerfile',
    epilog="Example: Font2Images.py CourierPrime.ttf 'Courier Prime' 8 12 14 16"
)

parser.add_argument("fontfile", help='Path to ttf font file to convert')
parser.add_argument("fontname", help="Name of the font")
parser.add_argument("sizes", nargs='+', help="Sizes of the font to convert")
parser.add_argument("--charset", required=False,
                    help='Path to file containing character set. Default is used if none provided.')

args = parser.parse_args()
sizes = args.sizes
charset: str = '' if args.charset else string.digits + \
    string.ascii_letters + string.punctuation + ' '
fontname = Path(args.fontfile).stem.replace(' ', '_')

if charset == '':
    # read from file
    cfile = open(args.charset, 'r')
    charset = cfile.readline()
    cfile.close()

print(
    f"Generating images for the following sizes from {args.fontfile}: {', '.join(f'{x}pt' for x in sizes)}...")
print(f"Character Set: {charset}")

print()


def determineMaxCharsetHeight(charset, font):
    """
    Given a charset and font, determine the minimum and maximum height of any character in the character set
    """
    min = 100000
    max = 0
    for c in charset:
        w, h = font.getsize(c)
        if h > max:
            max = h
        if h < min:
            min = h

    return (min, max)


def generateCharacterImage(character, font, characterHeight) -> Image.Image:
    w, h = font.getsize(character)
    image = Image.new('1', (w, characterHeight), 1)
    draw = ImageDraw.Draw(image)
    draw.text((0, 0), character, font=font)
    return image


for s in sizes:
    print(f"Generating images for {s}pt:")
    dir = f'./{fontname}_{s}pt/'
    os.makedirs(dir)

    font = ImageFont.truetype(args.fontfile, int(s))

    minHeight, maxHeight = determineMaxCharsetHeight(
        charset, font)  # all characters must have the same height, this helps us clamp to a height where all chars will fit

    print(f'\tMinimum/Maximum height: {minHeight}px/{maxHeight}px')

    i = 0
    # store filenames and what character they represent as well as other important information about the font
    config = {
        "name": args.fontname,
        "fontsize": int(s),
        "charset": charset
    }
    for char in charset:
        img = generateCharacterImage(char, font, maxHeight)
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

    print()

print()
