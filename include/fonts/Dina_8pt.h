/**
 * This file was generated automatically using scripts/fontmaking/Images2FontHeaders.py
 *
 * Font: Dina
 * Font Size: 8pt
 * Generated On: 13 October 2024 @ 7:27 PM
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
class Dina_8pt : public AbstractFont {
  private:
    const std::string charset =
        "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ ";

  public:
    Dina_8pt() {}
    uint8_t GetFontSize() const override { return 8; }
    uint8_t GetHeight() const override { return 13; }
    std::string GetFontName() override { return "Dina"; }
    std::string GetCharacterSet() const override { return charset; }
    const uint8_t* GetBitmapData() const override { return bitmap.data(); }
    const uint8_t* GetCharacterWidths() const override { return charWidths.data(); }

  private:
    const std::vector<uint8_t> charWidths = {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
                                             7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
                                             7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
                                             7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7};

    const std::vector<uint8_t> bitmap = {
        0, 0,   226, 36,  202, 149, 50, 68, 112, 0,   0,   0,   0, 0,   65,  133, 2,   4,   8,  16, 248, 0,  0,   0,
        0, 0,   226, 32,  65,  4,   16, 64, 248, 0,   0,   0,   0, 0,   226, 32,  67,  1,   2,  68, 112, 0,  0,   0,
        0, 0,   16,  97,  68,  145, 63, 4,  8,   0,   0,   0,   0, 1,   242, 4,   15,  1,   2,  68, 112, 0,  0,   0,
        0, 0,   97,  4,   15,  17,  34, 68, 112, 0,   0,   0,   0, 1,   240, 32,  129, 4,   8,  32, 64,  0,  0,   0,
        0, 0,   226, 36,  71,  17,  34, 68, 112, 0,   0,   0,   0, 0,   226, 36,  72,  143, 2,  8,  96,  0,  0,   0,
        0, 0,   0,   3,   128, 143, 34, 68, 120, 0,   0,   0,   0, 129, 2,   7,   136, 145, 34, 68, 240, 0,  0,   0,
        0, 0,   0,   3,   136, 144, 32, 68, 112, 0,   0,   0,   0, 8,   16,  35,  200, 145, 34, 68, 120, 0,  0,   0,
        0, 0,   0,   3,   136, 159, 32, 68, 112, 0,   0,   0,   0, 56,  129, 7,   132, 8,   16, 32, 64,  0,  0,   0,
        0, 0,   0,   3,   200, 145, 34, 68, 120, 16,  35,  128, 0, 129, 2,   7,   136, 145, 34, 68, 136, 0,  0,   0,
        0, 32,  64,  3,   2,   4,   8,  16, 112, 0,   0,   0,   0, 16,  32,  3,   129, 2,   4,  8,  16,  35, 128, 0,
        0, 129, 2,   4,   73,  20,  56, 72, 136, 0,   0,   0,   0, 96,  64,  129, 2,   4,   8,  16, 48,  0,  0,   0,
        0, 0,   0,   6,   138, 149, 42, 84, 168, 0,   0,   0,   0, 0,   0,   7,   136, 145, 34, 68, 136, 0,  0,   0,
        0, 0,   0,   3,   136, 145, 34, 68, 112, 0,   0,   0,   0, 0,   0,   7,   136, 145, 34, 68, 241, 2,  4,   0,
        0, 0,   0,   3,   200, 145, 34, 68, 120, 16,  32,  64,  0, 0,   0,   5,   140, 144, 32, 64, 128, 0,  0,   0,
        0, 0,   0,   3,   136, 142, 2,  68, 112, 0,   0,   0,   0, 0,   129, 7,   132, 8,   16, 32, 56,  0,  0,   0,
        0, 0,   0,   4,   72,  145, 34, 68, 120, 0,   0,   0,   0, 0,   0,   4,   72,  138, 20, 16, 32,  0,  0,   0,
        0, 0,   0,   4,   72,  149, 42, 40, 80,  0,   0,   0,   0, 0,   0,   4,   69,  4,   8,  40, 136, 0,  0,   0,
        0, 0,   0,   4,   72,  145, 34, 68, 120, 16,  35,  128, 0, 0,   0,   7,   193, 4,   16, 64, 248, 0,  0,   0,
        0, 0,   64,  130, 133, 14,  34, 68, 136, 0,   0,   0,   0, 1,   226, 36,  79,  17,  34, 68, 240, 0,  0,   0,
        0, 0,   226, 36,  8,   16,  32, 68, 112, 0,   0,   0,   0, 1,   194, 68,  72,  145, 34, 72, 224, 0,  0,   0,
        0, 1,   242, 4,   15,  16,  32, 64, 248, 0,   0,   0,   0, 1,   242, 4,   15,  16,  32, 64, 128, 0,  0,   0,
        0, 0,   226, 36,  8,   19,  34, 68, 112, 0,   0,   0,   0, 1,   18,  36,  79,  145, 34, 68, 136, 0,  0,   0,
        0, 0,   224, 129, 2,   4,   8,  16, 112, 0,   0,   0,   0, 0,   112, 32,  64,  129, 34, 68, 112, 0,  0,   0,
        0, 1,   18,  69,  14,  18,  36, 68, 136, 0,   0,   0,   0, 1,   2,   4,   8,   16,  32, 64, 248, 0,  0,   0,
        0, 1,   19,  101, 74,  145, 34, 68, 136, 0,   0,   0,   0, 1,   19,  37,  74,  147, 34, 68, 136, 0,  0,   0,
        0, 0,   226, 36,  72,  145, 34, 68, 112, 0,   0,   0,   0, 1,   226, 36,  72,  158, 32, 64, 128, 0,  0,   0,
        0, 0,   226, 36,  72,  145, 34, 72, 104, 16,  0,   0,   0, 1,   226, 36,  79,  18,  34, 68, 136, 0,  0,   0,
        0, 0,   226, 36,  7,   1,   2,  68, 112, 0,   0,   0,   0, 1,   240, 129, 2,   4,   8,  16, 32,  0,  0,   0,
        0, 1,   18,  36,  72,  145, 34, 68, 112, 0,   0,   0,   0, 1,   18,  36,  69,  10,  20, 16, 32,  0,  0,   0,
        0, 1,   18,  36,  74,  149, 28, 40, 80,  0,   0,   0,   0, 1,   18,  34,  130, 4,   20, 68, 136, 0,  0,   0,
        0, 1,   18,  36,  69,  4,   8,  16, 32,  0,   0,   0,   0, 1,   240, 65,  2,   8,   16, 64, 248, 0,  0,   0,
        0, 0,   64,  129, 2,   4,   8,  0,  32,  0,   0,   0,   0, 80,  161, 64,  0,   0,   0,  0,  0,   0,  0,   0,
        0, 0,   161, 71,  197, 10,  62, 40, 80,  0,   0,   0,   0, 32,  226, 165, 7,   5,   10, 84, 112, 64, 0,   0,
        0, 65,  65,  32,  130, 8,   36, 20, 16,  0,   0,   0,   0, 32,  161, 65,  6,   146, 36, 72, 104, 0,  0,   0,
        0, 32,  64,  128, 0,   0,   0,  0,  0,   0,   0,   0,   0, 16,  64,  130, 4,   8,   16, 32, 32,  64, 64,  0,
        0, 64,  64,  128, 129, 2,   4,  8,  32,  65,  0,   0,   0, 0,   0,   2,   130, 31,  8,  40, 0,   0,  0,   0,
        0, 0,   0,   1,   2,   31,  8,  16, 0,   0,   0,   0,   0, 0,   0,   0,   0,   0,   0,  16, 32,  65, 0,   0,
        0, 0,   0,   0,   0,   31,  0,  0,  0,   0,   0,   0,   0, 0,   0,   0,   0,   0,   0,  16, 32,  0,  0,   0,
        0, 8,   16,  64,  130, 4,   16, 32, 129, 0,   0,   0,   0, 0,   0,   1,   2,   0,   0,  16, 32,  0,  0,   0,
        0, 0,   0,   1,   2,   0,   0,  16, 32,  65,  0,   0,   0, 0,   0,   32,  130, 8,   8,  8,  8,   0,  0,   0,
        0, 0,   0,   0,   15,  128, 62, 0,  0,   0,   0,   0,   0, 0,   2,   2,   2,   2,   8,  32, 128, 0,  0,   0,
        0, 0,   226, 32,  65,  4,   8,  0,  32,  0,   0,   0,   0, 0,   226, 36,  202, 149, 38, 64, 120, 0,  0,   0,
        0, 112, 129, 2,   4,   8,   16, 32, 64,  129, 192, 0,   0, 129, 1,   2,   2,   4,   4,  8,  8,   16, 0,   0,
        0, 112, 32,  64,  129, 2,   4,  8,  16,  33,  192, 0,   0, 32,  65,  66,  136, 145, 0,  0,  0,   0,  0,   0,
        0, 0,   0,   0,   0,   0,   0,  0,  3,   248, 0,   0,   0, 64,  64,  0,   0,   0,   0,  0,  0,   0,  0,   0,
        0, 24,  64,  129, 2,   24,  8,  16, 32,  64,  96,  0,   0, 32,  64,  129, 2,   4,   8,  16, 32,  64, 128, 0,
        0, 192, 64,  129, 2,   3,   8,  16, 32,  67,  0,   0,   0, 0,   0,   0,   4,   149, 36, 0,  0,   0,  0,   0,
        0, 0,   0,   0,   0,   0,   0,  0,  0,   0,   0,   0
    };
};
} // namespace epaperapi::fonts
