"""
This script converts 1-bit .bmp files to C++ header files usable by ws-epaper-api
"""
import common
import argparse
from pathlib import Path
import os

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
    prog='Bitmap2HeaderFiles.py',
    description='Converts 1-bit .bmp files to C++ header files usable by ws-epaper-api'
)

parser.add_argument('files', nargs='+', help='Files to convert')

parser.add_argument('--invert', action='store_true', help='Inverts the image')

args = parser.parse_args()

files = args.files
invert = args.invert


def packBytes(bits: bytearray):
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


def bytesToString(bytes: bytearray):
    return ','.join(str(b) for b in bytes)


def generateHeaderfile(width, height, bytes):
    return f"""/**
 * This file was generated automatically using scripts/bitmapconversion/Bitmap2HeaderFiles.py
 */
 
#pragma once

#include "AbstractBitmap.h"

#include <vector>

namespace epaperapi::bitmaps {{
class TestBitmap : public AbstractBitmap {{
  public:
    /// @brief Get the width of the bitmap in pixels
    uint16_t GetWidth() const override {{ return {width}; }}

    /// @brief Get the height of the bitmap in pixels
    uint16_t GetHeight() const override {{ return {height}; }}

    const uint8_t* GetBitmapData() const override {{ return bitmap.data(); }}

  private:
    const std::vector<uint8_t> bitmap = {{{bytesToString(bytes)}}};
}};
}} // namespace epaperapi::bitmaps
"""


for file in files:
    print(f'Processing {file}...')

    if not Path(file).exists():
        print(f'\tSkipping {file} as it does not exist')
        continue

    # read bmp file using PIL
    data = bytearray()
    img = PIL.Image.open(file)

    if img.mode not in '1P':
        print(
            f'\tSkipping {file} as it is not a 1-bit image (image mode was \'{img.mode}\' - expected \'1\' or \'P\')')
        continue

    arr: np.ndarray = np.asarray(img, dtype=np.uint8)
    arr = arr.flatten()

    if invert:
        arr = 1 - arr
        print('\tInverted image')

    packed = packBytes(bytearray(arr))

    # save
    hf = open('Bitmap.h', 'w')
    hf.write(generateHeaderfile(img.width, img.height, packed))
    hf.close()

    print('\tGenerated headerfile \'Bitmap.h\'')
