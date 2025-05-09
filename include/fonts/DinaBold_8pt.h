/**
 * This file was generated automatically using scripts/fontmaking/Images2FontHeaders.py
 *
 * Font: Dina Bold
 * Font Size: 8pt
 * Generated On: 13 October 2024 @ 7:45 PM
 *
 * License:
 *
 * Copyright (c) 2005-2013 Joergen Ibsen
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#pragma once

#include "AbstractFont.h"

#include <vector>

namespace epaperapi::fonts {
class DinaBold_8pt : public AbstractFont {
  private:
    const std::string charset =
        "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ ";

  public:
    DinaBold_8pt() {}
    uint8_t GetFontSize() const override { return 8; }
    uint8_t GetHeight() const override { return 13; }
    std::string GetFontName() override { return "Dina Bold"; }
    std::string GetCharacterSet() const override { return charset; }
    const uint8_t* GetBitmapData() const override { return bitmap.data(); }
    const uint8_t* GetCharacterWidths() const override { return charWidths.data(); }

  private:
    const std::vector<uint8_t> charWidths = {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
                                             7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
                                             7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
                                             7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7};

    const std::vector<uint8_t> bitmap = {
        0, 1,   230, 109, 219, 187, 118, 204, 240, 0,   0,   0,   0, 0,   65,  135, 22,  12,  24,  49,  248, 0,   0,   0,
        0, 1,   230, 96,  195, 12,  48,  193, 248, 0,   0,   0,   0, 1,   230, 96,  199, 3,   6,   204, 240, 0,   0,   0,
        0, 0,   48,  227, 205, 179, 127, 12,  24,  0,   0,   0,   0, 3,   246, 12,  31,  3,   6,   204, 240, 0,   0,   0,
        0, 0,   195, 12,  31,  51,  102, 204, 240, 0,   0,   0,   0, 3,   240, 97,  131, 12,  24,  96,  192, 0,   0,   0,
        0, 1,   230, 108, 207, 51,  102, 204, 240, 0,   0,   0,   0, 1,   230, 108, 217, 159, 6,   24,  96,  0,   0,   0,
        0, 0,   0,   7,   129, 159, 102, 204, 248, 0,   0,   0,   1, 131, 6,   15,  153, 179, 102, 205, 240, 0,   0,   0,
        0, 0,   0,   7,   153, 176, 96,  204, 240, 0,   0,   0,   0, 24,  48,  103, 217, 179, 102, 204, 248, 0,   0,   0,
        0, 0,   0,   7,   153, 191, 96,  204, 240, 0,   0,   0,   0, 121, 131, 15,  140, 24,  48,  96,  192, 0,   0,   0,
        0, 0,   0,   7,   217, 179, 102, 204, 248, 48,  103, 128, 1, 131, 6,   15,  153, 179, 102, 205, 152, 0,   0,   0,
        0, 96,  192, 7,   6,   12,  24,  48,  240, 0,   0,   0,   0, 48,  96,  7,   131, 6,   12,  24,  48,  103, 128, 0,
        1, 131, 6,   12,  219, 60,  120, 217, 152, 0,   0,   0,   0, 224, 193, 131, 6,   12,  24,  48,  112, 0,   0,   0,
        0, 0,   0,   8,   89,  191, 126, 205, 152, 0,   0,   0,   0, 0,   0,   15,  153, 179, 102, 205, 152, 0,   0,   0,
        0, 0,   0,   7,   153, 179, 102, 204, 240, 0,   0,   0,   0, 0,   0,   15,  153, 179, 102, 205, 243, 6,   12,  0,
        0, 0,   0,   7,   217, 179, 102, 204, 248, 48,  96,  192, 0, 0,   0,   13,  157, 176, 96,  193, 128, 0,   0,   0,
        0, 0,   0,   7,   153, 158, 6,   204, 240, 0,   0,   0,   0, 1,   131, 15,  140, 24,  48,  96,  120, 0,   0,   0,
        0, 0,   0,   12,  217, 179, 102, 204, 248, 0,   0,   0,   0, 0,   0,   12,  217, 158, 60,  48,  96,  0,   0,   0,
        0, 0,   0,   12,  217, 191, 126, 205, 8,   0,   0,   0,   0, 0,   0,   12,  207, 12,  24,  121, 152, 0,   0,   0,
        0, 0,   0,   12,  217, 179, 102, 204, 248, 48,  103, 128, 0, 0,   0,   15,  195, 12,  48,  193, 248, 0,   0,   0,
        0, 0,   193, 135, 143, 51,  126, 205, 152, 0,   0,   0,   0, 3,   230, 108, 223, 51,  102, 205, 240, 0,   0,   0,
        0, 1,   230, 108, 24,  48,  96,  204, 240, 0,   0,   0,   0, 3,   198, 204, 217, 179, 102, 217, 224, 0,   0,   0,
        0, 3,   246, 12,  31,  48,  96,  193, 248, 0,   0,   0,   0, 3,   246, 12,  31,  48,  96,  193, 128, 0,   0,   0,
        0, 1,   230, 108, 24,  55,  102, 204, 240, 0,   0,   0,   0, 3,   54,  108, 223, 179, 102, 205, 152, 0,   0,   0,
        0, 1,   225, 131, 6,   12,  24,  48,  240, 0,   0,   0,   0, 0,   112, 96,  193, 131, 102, 204, 240, 0,   0,   0,
        0, 3,   54,  109, 158, 54,  102, 205, 152, 0,   0,   0,   0, 3,   6,   12,  24,  48,  96,  193, 248, 0,   0,   0,
        0, 2,   22,  111, 223, 179, 102, 205, 152, 0,   0,   0,   0, 3,   55,  111, 219, 179, 102, 205, 152, 0,   0,   0,
        0, 1,   230, 108, 217, 179, 102, 204, 240, 0,   0,   0,   0, 3,   230, 108, 217, 190, 96,  193, 128, 0,   0,   0,
        0, 1,   230, 108, 217, 179, 102, 200, 248, 48,  0,   0,   0, 3,   230, 108, 223, 54,  102, 205, 152, 0,   0,   0,
        0, 1,   230, 108, 15,  3,   6,   204, 240, 0,   0,   0,   0, 3,   241, 131, 6,   12,  24,  48,  96,  0,   0,   0,
        0, 3,   54,  108, 217, 179, 102, 204, 240, 0,   0,   0,   0, 3,   54,  108, 217, 158, 60,  48,  96,  0,   0,   0,
        0, 3,   54,  108, 217, 191, 126, 205, 8,   0,   0,   0,   0, 3,   54,  103, 134, 12,  60,  205, 152, 0,   0,   0,
        0, 3,   54,  108, 207, 12,  24,  48,  96,  0,   0,   0,   0, 3,   240, 97,  134, 24,  48,  193, 248, 0,   0,   0,
        0, 0,   193, 131, 6,   12,  24,  0,   96,  0,   0,   0,   0, 217, 179, 96,  0,   0,   0,   0,   0,   0,   0,   0,
        0, 1,   163, 79,  205, 26,  126, 104, 208, 0,   0,   0,   0, 33,  230, 175, 15,  15,  10,  212, 240, 64,  0,   0,
        0, 195, 195, 97,  134, 24,  108, 188, 48,  0,   0,   0,   0, 97,  163, 67,  14,  182, 108, 216, 232, 0,   0,   0,
        0, 96,  193, 128, 0,   0,   0,   0,   0,   0,   0,   0,   0, 24,  96,  195, 6,   12,  24,  48,  48,  96,  96,  0,
        0, 192, 193, 129, 131, 6,   12,  24,  96,  195, 0,   0,   0, 0,   0,   12,  207, 63,  60,  204, 0,   0,   0,   0,
        0, 0,   0,   3,   6,   63,  24,  48,  0,   0,   0,   0,   0, 0,   0,   0,   0,   0,   0,   48,  96,  195, 0,   0,
        0, 0,   0,   0,   0,   63,  0,   0,   0,   0,   0,   0,   0, 0,   0,   0,   0,   0,   0,   48,  96,  0,   0,   0,
        0, 8,   48,  97,  131, 12,  24,  96,  193, 0,   0,   0,   0, 0,   0,   3,   6,   0,   0,   48,  96,  0,   0,   0,
        0, 0,   0,   3,   6,   0,   0,   48,  96,  195, 0,   0,   0, 0,   0,   97,  134, 24,  24,  24,  24,  0,   0,   0,
        0, 0,   0,   0,   31,  128, 126, 0,   0,   0,   0,   0,   0, 0,   6,   6,   6,   6,   24,  97,  128, 0,   0,   0,
        0, 1,   230, 96,  195, 12,  24,  0,   96,  0,   0,   0,   0, 1,   230, 108, 219, 183, 102, 192, 248, 0,   0,   0,
        0, 120, 193, 131, 6,   12,  24,  48,  96,  193, 224, 0,   0, 129, 131, 3,   6,   6,   12,  12,  24,  16,  0,   0,
        0, 240, 96,  193, 131, 6,   12,  24,  48,  99,  192, 0,   0, 96,  195, 199, 153, 179, 0,   0,   0,   0,   0,   0,
        0, 0,   0,   0,   0,   0,   0,   0,   3,   248, 0,   0,   0, 96,  96,  0,   0,   0,   0,   0,   0,   0,   0,   0,
        0, 56,  193, 131, 6,   56,  24,  48,  96,  192, 224, 0,   0, 96,  193, 131, 6,   12,  24,  48,  96,  193, 128, 0,
        1, 192, 193, 131, 6,   7,   24,  48,  96,  199, 0,   0,   0, 0,   0,   0,   12,  191, 76,  0,   0,   0,   0,   0,
        0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0
    };
};
} // namespace epaperapi::fonts
