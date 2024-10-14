/**
 * This file was generated automatically using scripts/fontmaking/Images2FontHeaders.py
 *
 * Font: Dina Italic
 * Font Size: 8pt
 * Generated On: 13 October 2024 @ 7:50 PM
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
class DinaItalic_8pt : public AbstractFont {
  private:
    const std::string charset =
        "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ ";

  public:
    DinaItalic_8pt() {}
    uint8_t GetFontSize() const override { return 8; }
    uint8_t GetHeight() const override { return 13; }
    std::string GetFontName() override { return "Dina Italic"; }
    std::string GetCharacterSet() const override { return charset; }
    const uint8_t* GetBitmapData() const override { return bitmap.data(); }
    const uint8_t* GetCharacterWidths() const override { return charWidths.data(); }

  private:
    const std::vector<uint8_t> charWidths = {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
                                             7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
                                             7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
                                             7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7};

    const std::vector<uint8_t> bitmap = {
        0, 0,  226, 36,  210, 169, 100, 136, 224, 0,   0,   0, 0, 0,   97,  68,  130, 4,   16,  33,  240, 0,   0,   0,
        0, 0,  113, 16,  33,  140, 32,  129, 240, 0,   0,   0, 0, 0,   113, 16,  67,  1,   2,   136, 224, 0,   0,   0,
        0, 0,  16,  97,  69,  18,  126, 16,  32,  0,   0,   0, 0, 0,   249, 4,   15,  1,   2,   136, 224, 0,   0,   0,
        0, 0,  113, 4,   15,  33,  66,  136, 224, 0,   0,   0, 0, 1,   240, 32,  130, 8,   16,  64,  128, 0,   0,   0,
        0, 0,  113, 20,  71,  17,  66,  136, 224, 0,   0,   0, 0, 0,   113, 20,  40,  143, 4,   16,  192, 0,   0,   0,
        0, 0,  0,   3,   128, 159, 66,  136, 240, 0,   0,   0, 0, 64,  129, 7,   136, 145, 68,  137, 224, 0,   0,   0,
        0, 0,  0,   3,   136, 144, 64,  136, 224, 0,   0,   0, 0, 4,   8,   19,  200, 145, 68,  136, 240, 0,   0,   0,
        0, 0,  0,   3,   136, 159, 64,  136, 224, 0,   0,   0, 0, 28,  64,  135, 132, 8,   32,  64,  128, 0,   0,   0,
        0, 0,  0,   3,   200, 145, 68,  136, 240, 32,  142, 0, 0, 64,  129, 7,   136, 145, 68,  137, 16,  0,   0,   0,
        0, 16, 32,  3,   2,   4,   16,  32,  224, 0,   0,   0, 0, 8,   16,  3,   129, 2,   4,   16,  32,  71,  0,   0,
        0, 64, 129, 4,   73,  20,  80,  145, 16,  0,   0,   0, 0, 48,  32,  65,  2,   4,   16,  32,  96,  0,   0,   0,
        0, 0,  0,   6,   138, 149, 84,  169, 80,  0,   0,   0, 0, 0,   0,   7,   136, 145, 68,  137, 16,  0,   0,   0,
        0, 0,  0,   3,   136, 145, 68,  136, 224, 0,   0,   0, 0, 0,   0,   3,   196, 72,  162, 68,  242, 4,   8,   0,
        0, 0,  0,   3,   200, 145, 68,  136, 240, 64,  129, 0, 0, 0,   0,   5,   140, 144, 64,  129, 0,   0,   0,   0,
        0, 0,  0,   3,   136, 140, 4,   136, 224, 0,   0,   0, 0, 0,   64,  135, 132, 8,   32,  64,  112, 0,   0,   0,
        0, 0,  0,   4,   72,  145, 68,  136, 240, 0,   0,   0, 0, 0,   0,   4,   72,  138, 20,  48,  64,  0,   0,   0,
        0, 0,  0,   4,   72,  169, 84,  209, 32,  0,   0,   0, 0, 0,   0,   4,   69,  4,   16,  81,  16,  0,   0,   0,
        0, 0,  0,   4,   72,  145, 68,  136, 240, 64,  142, 0, 0, 0,   0,   7,   193, 12,  32,  129, 240, 0,   0,   0,
        0, 0,  48,  162, 68,  159, 34,  133, 8,   0,   0,   0, 0, 0,   241, 20,  79,  18,  66,  133, 240, 0,   0,   0,
        0, 0,  113, 20,  8,   32,  64,  136, 224, 0,   0,   0, 0, 0,   241, 18,  40,  81,  66,  137, 224, 0,   0,   0,
        0, 0,  249, 4,   15,  16,  64,  129, 240, 0,   0,   0, 0, 0,   249, 4,   15,  16,  64,  129, 0,   0,   0,   0,
        0, 0,  113, 20,  8,   35,  66,  136, 224, 0,   0,   0, 0, 0,   137, 20,  79,  145, 68,  137, 16,  0,   0,   0,
        0, 0,  112, 65,  2,   4,   16,  32,  224, 0,   0,   0, 0, 0,   56,  16,  32,  129, 66,  136, 224, 0,   0,   0,
        0, 0,  137, 36,  142, 18,  68,  137, 16,  0,   0,   0, 0, 0,   129, 4,   8,   16,  64,  129, 240, 0,   0,   0,
        0, 0,  137, 181, 202, 145, 68,  137, 16,  0,   0,   0, 0, 0,   137, 21,  74,  149, 68,  137, 16,  0,   0,   0,
        0, 0,  113, 20,  40,  97,  66,  136, 224, 0,   0,   0, 0, 0,   241, 18,  40,  158, 32,  129, 0,   0,   0,   0,
        0, 0,  113, 20,  40,  97,  74,  136, 232, 16,  0,   0, 0, 0,   241, 20,  47,  146, 68,  133, 8,   0,   0,   0,
        0, 0,  113, 18,  2,   2,   4,   136, 224, 0,   0,   0, 0, 0,   248, 64,  130, 4,   16,  32,  64,  0,   0,   0,
        0, 0,  137, 20,  72,  145, 68,  136, 224, 0,   0,   0, 0, 1,   10,  20,  72,  146, 40,  32,  64,  0,   0,   0,
        0, 0,  137, 20,  40,  149, 90,  217, 16,  0,   0,   0, 0, 0,   137, 18,  67,  12,  36,  137, 16,  0,   0,   0,
        0, 1,  10,  18,  69,  4,   8,   32,  64,  0,   0,   0, 0, 0,   248, 32,  130, 8,   32,  129, 240, 0,   0,   0,
        0, 0,  32,  64,  130, 4,   0,   32,  64,  0,   0,   0, 0, 80,  161, 64,  0,   0,   0,   0,   0,   0,   0,   0,
        0, 0,  161, 71,  197, 20,  124, 80,  160, 0,   0,   0, 0, 16,  242, 85,  6,   6,   10,  164, 240, 128, 0,   0,
        0, 65, 65,  0,   198, 48,  8,   40,  32,  0,   0,   0, 0, 16,  80,  160, 134, 19,  68,  144, 216, 0,   0,   0,
        0, 32, 64,  128, 0,   0,   0,   0,   0,   0,   0,   0, 0, 16,  65,  2,   8,   16,  32,  64,  64,  128, 128, 0,
        0, 64, 64,  128, 129, 2,   4,   16,  32,  130, 0,   0, 0, 0,   0,   2,   130, 63,  16,  80,  0,   0,   0,   0,
        0, 0,  0,   1,   2,   63,  16,  32,  0,   0,   0,   0, 0, 0,   0,   0,   0,   0,   0,   16,  32,  130, 0,   0,
        0, 0,  0,   0,   0,   31,  0,   0,   0,   0,   0,   0, 0, 0,   0,   0,   0,   0,   0,   32,  64,  0,   0,   0,
        0, 8,  32,  65,  2,   8,   16,  64,  130, 0,   0,   0, 0, 0,   0,   1,   2,   0,   0,   32,  64,  0,   0,   0,
        0, 0,  0,   1,   2,   0,   0,   32,  65,  4,   0,   0, 0, 0,   0,   32,  130, 8,   16,  16,  32,  0,   0,   0,
        0, 0,  0,   0,   15,  128, 124, 0,   0,   0,   0,   0, 0, 0,   0,   129, 1,   2,   8,   32,  128, 0,   0,   0,
        0, 0,  226, 32,  65,  4,   0,   32,  64,  0,   0,   0, 0, 0,   226, 36,  75,  42,  76,  128, 240, 0,   0,   0,
        0, 56, 64,  130, 4,   8,   16,  64,  129, 3,   128, 0, 0, 129, 1,   2,   2,   4,   4,   8,   8,   16,  0,   0,
        0, 56, 16,  32,  129, 2,   4,   16,  32,  67,  128, 0, 0, 32,  65,  66,  137, 18,  0,   0,   0,   0,   0,   0,
        0, 0,  0,   0,   0,   0,   0,   0,   3,   248, 0,   0, 0, 64,  64,  0,   0,   0,   0,   0,   0,   0,   0,   0,
        0, 12, 32,  65,  2,   24,  8,   32,  64,  128, 192, 0, 0, 16,  32,  65,  2,   4,   8,   16,  64,  129, 0,   0,
        0, 96, 32,  65,  2,   3,   8,   16,  64,  134, 0,   0, 0, 0,   0,   0,   4,   149, 36,  0,   0,   0,   0,   0,
        0, 0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0
    };
};
} // namespace epaperapi::fonts
