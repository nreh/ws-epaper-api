"""
This script aids in the creation of fonts by converting images generated by the 'Font2Images.py' script into C++ header files
usable by ws-epaper-api.
"""

import argparse
from datetime import datetime
import traceback

import common
import os
from pathlib import Path
import json

common.requirePackages(["PIL", "numpy"])

# autopep8: off
import string 
import PIL.Image
from PIL import Image
from PIL import ImageFont
from PIL import ImageDraw
import numpy as np
import PIL.ImageOps
# autopep8: on

parser = argparse.ArgumentParser(
    prog='Font2Images.py',
    description='Using images generated from .ttf files, generates C++ header files that can be used for rendering text by ws-epaper-api.'
)

parser.add_argument("directories", nargs='+',
                    help='Directory or directories containing images and a config.json file')
parser.add_argument(
    '--nopack', help='When given, the bytes will not be packed - useful for debugging', action='store_true')

parser.add_argument(
    '--license', help='When given, includes given license in the header of C++ file', default=None)

parser.add_argument(
    '--debug', help='Enable debug tracebacks', action='store_true')

parser.add_argument(
    '--invertmask', help='Characters whose pixels should be inverted prior to generating bytes. Useful for when bitmap save formats cause issues with coloring.', default='')

parser.add_argument(
    '--autoinvert', help='When given, any character that is detected to have its colors reversed will be automatically inverted. Use --invertmask to specify which characters to never invert. Useful for when bitmap save formats cause issues with coloring.', action='store_true')

args = parser.parse_args()
dirs = args.directories
nopack = args.nopack
invertmask = args.invertmask
autoinvert = args.autoinvert
license = args.license

debug = args.debug

if license != None:
    print(f'Using license: {license}')

if nopack:
    print("Warning --nopack flag given means the generated headerfile will probably not be usable.")

print()

autoInvertedChars = []


def packElement(bits: bytearray):
    """
    Give an array of bits with 1 bit per byte, packs them so that each byte now represents 8 bits in the given bytearray.
    """
    # Ensure the input length is a multiple of 8 by padding with 0s if necessary
    padding = (8 - len(bits) % 8) % 8
    bits.extend([0] * padding)

    # Initialize the packed bytearray
    packed = bytearray()

    # Iterate over the bits in chunks of 8
    for i in range(0, len(bits), 8):
        # Pack each chunk of 8 bits into a single byte
        byte = 0
        for j in range(8):
            byte |= (bits[i + j] << (7 - j))
        if byte > 255 or byte < 0:
            print(f'Warning byte is {byte}')
        packed.append(byte)

    return packed


def convertImageToBytes(filename, character, pack):
    global autoInvertedChars

    # Format of bytes:
    #
    # The bits are packed so that 1 byte contains 8 pixels worth of bits.
    # The last byte contains padded zeros at the end so that we remain
    # aligned on byte boundaries - this helps make indexing easier in our C++ code.

    data = bytearray()
    img = PIL.Image.open(filename)

    if img.width > 255:
        # character is too wide!
        raise RuntimeError(
            f'character \'{character}\' has a width of {img.width}px which is too big')

    # convert to bits
    arr: np.ndarray = np.asarray(img, dtype=np.uint8)

    arr = arr.flatten()

    # count number of black pixels vs white
    white = 0
    black = 0
    for i in arr:
        if i == 1:
            white += 1
        else:
            black += 1

    doInvert = True

    if black > white:
        # image might not need to be inverted here
        if autoinvert:
            if character in invertmask:
                print(
                    f'\tCharacter \'{character}\' not inverted due to it being in --invertmask')
            else:
                autoInvertedChars.append(character)
                doInvert = False  # "invert" the colors by basically not inverting
        else:
            autoInvertedChars.append(character)

    if autoinvert == False and character in invertmask:
        doInvert = False
        print(
            f'\tCharacter \'{character}\' inverted due to it being in --invertmask')

    if doInvert:
        arr = 1 - arr  # invert

    if pack:
        data += packElement(bytearray(arr))
    else:
        data += bytearray(arr)

    return img.height, img.width, data


def bytesToString(bytes: bytearray):
    return ','.join(str(b) for b in bytes)


def cppFontname(fontname: str, size: str):
    return fontname.replace(' ', '') + "_" + str(size) + "pt"


def generateDescription(fontname, size, generatedOn, license):
    lines = []
    lines.append(f' * Font: {fontname}')
    lines.append(f' * Font Size: {size}pt')
    lines.append(f' * Generated On: {generatedOn}')
    if license != None:
        lines.append(f' * License: {license}')

    return '\n'.join(lines)


def generateHeaderfile(widths, bytes, fontname, size, height, license):
    cc = charset.replace('\\', '\\\\').replace('"', '\\"')
    return f"""/**
 * This file was generated automatically using scripts/fontmaking/Images2FontHeaders.py
 * 
{generateDescription(fontname, size, datetime.now().strftime("%-d %B %Y @ %-I:%M %p"), license)}
 */
 
#pragma once

#include "AbstractFont.h"

#include <vector>

namespace epaperapi::fonts {{
class {cppFontname(fontname, size)} : public AbstractFont {{
  private:
    const std::string charset = "{cc}";

  public:
    {cppFontname(fontname, size)}() {{}}
    uint8_t GetFontSize() const override {{ return {size}; }}
    uint8_t GetHeight() const override {{ return {height}; }}
    std::string GetFontName() override {{ return "{fontname}"; }}
    std::string GetCharacterSet() const override {{ return charset; }}
    const uint8_t* GetBitmapData() const override {{ return bitmap.data(); }}
    const uint8_t* GetCharacterWidths() const override {{ return charWidths.data(); }}
    
  private:
    const std::vector<uint8_t> charWidths = {{{bytesToString(widths)}}};
    
    const std::vector<uint8_t> bitmap = {{{bytesToString(bytes)}}};
}};
}} // namespace epaperapi::fonts
"""


for d in dirs:
    try:
        print(f'Processing {d}...')

        # first make sure directory exists
        p = Path(d)
        if not p.exists():
            raise RuntimeError(f'directory doesn\'t exist')
        elif not p.is_dir():
            raise RuntimeError(f"path is not a directory")

        # try to find config.json
        configPath = p / Path('config.json')
        if not configPath.exists():
            raise RuntimeError(
                f'directory doesn\'t contain a config.json file ({configPath})')

        f = open(str(configPath), 'r')
        config = json.load(f)

        print(
            f'\tFound and loaded config.json (fontname = "{config["name"]})"')

        charset = config['charset']
        charwidths = bytearray()
        data = bytearray()

        heights = []

        for c in charset:
            bitmapName = config[c]
            print(f'\tReading {c} -> {bitmapName}')
            height, width, pixeldata = convertImageToBytes(
                p / bitmapName, c, not nopack)

            heights.append(height)

            charwidths.append(width)
            data += pixeldata

        # all heights should be the same
        first = heights[0]
        for i in heights:
            if i != first:
                raise RuntimeError(
                    'character images must have the same height in pixels')

        # generate headerfile from bytes
        content = generateHeaderfile(
            charwidths, data, config['name'], config['fontsize'], first, license)

        hf = open(f'{cppFontname(config["name"], config["fontsize"])}.h', 'w')
        hf.write(content)
        hf.close()

        print(
            f'\tGenerated {cppFontname(config["name"], config["fontsize"])}.h')

        if autoinvert:
            if len(autoInvertedChars) == 0:
                print('\tNo characters auto-inverted')
            else:
                print(
                    f'\tAutoinverted the following characters: {"".join(autoInvertedChars)}')
        else:
            if len(autoInvertedChars) > 0:
                print(
                    f'\tNote: The following characters may have broken colors: {"".join(autoInvertedChars)}')
                print(
                    '\tRerun this script with --autoinvert to automatically fix them')

    except Exception as e:
        print(f'ERROR: Skipping {d} - {str(e)}')

        if debug:
            print('--- Traceback ---')
            print(traceback.format_exc())
            print()

print()
print("Done!")

print()
