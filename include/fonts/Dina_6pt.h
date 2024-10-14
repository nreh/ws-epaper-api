/**
 * This file was generated automatically using scripts/fontmaking/Images2FontHeaders.py
 *
 * Font: Dina
 * Font Size: 6pt
 * Generated On: 13 October 2024 @ 7:04 PM
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
class Dina_6pt : public AbstractFont {
  private:
    const std::string charset =
        "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ ";

  public:
    Dina_6pt() {}
    uint8_t GetFontSize() const override { return 6; }
    uint8_t GetHeight() const override { return 10; }
    std::string GetFontName() override { return "Dina"; }
    std::string GetCharacterSet() const override { return charset; }
    const uint8_t* GetBitmapData() const override { return bitmap.data(); }
    const uint8_t* GetCharacterWidths() const override { return charWidths.data(); }

  private:
    const std::vector<uint8_t> charWidths = {6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
                                             6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
                                             6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
                                             6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6};

    const std::vector<uint8_t> bitmap = {
        0, 7,   38,  170, 172, 156, 0,  0,   0, 2,   24,  160, 130, 62,  0,   0,   0, 7,   34,  9,   200, 62,  0,   0,
        0, 7,   34,  48,  40,  156, 0,  0,   0, 1,   12,  82,  79,  132, 0,   0,   0, 15,  160, 240, 40,  156, 0,   0,
        0, 3,   16,  242, 40,  156, 0,  0,   0, 15,  130, 16,  132, 16,  0,   0,   0, 7,   34,  114, 40,  156, 0,   0,
        0, 7,   34,  137, 224, 156, 0,  0,   0, 0,   28,  9,   232, 158, 0,   0,   2, 8,   60,  138, 40,  188, 0,   0,
        0, 0,   28,  130, 8,   30,  0,  0,   0, 32,  158, 138, 40,  158, 0,   0,   0, 0,   28,  139, 232, 30,  0,   0,
        0, 228, 60,  65,  4,   16,  0,  0,   0, 0,   30,  138, 40,  158, 9,   192, 2, 8,   60,  138, 40,  162, 0,   0,
        0, 128, 24,  32,  130, 28,  0,  0,   0, 64,  28,  16,  65,  4,   19,  128, 2, 8,   34,  147, 137, 34,  0,   0,
        1, 130, 8,   32,  130, 12,  0,  0,   0, 0,   52,  170, 170, 170, 0,   0,   0, 0,   60,  138, 40,  162, 0,   0,
        0, 0,   28,  138, 40,  156, 0,  0,   0, 0,   60,  138, 40,  188, 130, 0,   0, 0,   30,  138, 40,  158, 8,   32,
        0, 0,   44,  202, 8,   32,  0,  0,   0, 0,   28,  129, 192, 188, 0,   0,   1, 4,   60,  65,  4,   14,  0,   0,
        0, 0,   34,  138, 40,  158, 0,  0,   0, 0,   34,  137, 69,  8,   0,   0,   0, 0,   34,  138, 170, 148, 0,   0,
        0, 0,   34,  80,  133, 34,  0,  0,   0, 0,   34,  138, 40,  158, 9,   192, 0, 0,   62,  16,  132, 62,  0,   0,
        0, 2,   8,   81,  200, 162, 0,  0,   0, 15,  34,  242, 40,  188, 0,   0,   0, 7,   34,  130, 8,   156, 0,   0,
        0, 14,  36,  138, 41,  56,  0,  0,   0, 15,  160, 226, 8,   62,  0,   0,   0, 15,  160, 226, 8,   32,  0,   0,
        0, 7,   32,  130, 232, 156, 0,  0,   0, 8,   162, 250, 40,  162, 0,   0,   0, 7,   8,   32,  130, 28,  0,   0,
        0, 3,   130, 10,  40,  156, 0,  0,   0, 8,   164, 163, 137, 34,  0,   0,   0, 8,   32,  130, 8,   62,  0,   0,
        0, 8,   182, 170, 40,  162, 0,  0,   0, 8,   178, 170, 104, 162, 0,   0,   0, 7,   34,  138, 40,  156, 0,   0,
        0, 15,  34,  139, 200, 32,  0,  0,   0, 7,   34,  138, 41,  26,  8,   0,   0, 15,  34,  242, 40,  162, 0,   0,
        0, 7,   32,  112, 40,  156, 0,  0,   0, 15,  136, 32,  130, 8,   0,   0,   0, 8,   162, 138, 40,  156, 0,   0,
        0, 8,   162, 137, 69,  8,   0,  0,   0, 8,   162, 170, 167, 20,  0,   0,   0, 8,   148, 33,  72,  162, 0,   0,
        0, 8,   162, 80,  130, 8,   0,  0,   0, 15,  132, 33,  8,   62,  0,   0,   0, 2,   8,   32,  128, 8,   0,   0,
        1, 69,  20,  0,   0,   0,   0,  0,   0, 5,   62,  81,  79,  148, 0,   0,   0, 135, 40,  112, 170, 156, 32,  0,
        3, 45,  4,   33,  5,   166, 0,  0,   0, 133, 8,   106, 73,  26,  0,   0,   0, 130, 8,   0,   0,   0,   0,   0,
        0, 66,  16,  65,  4,   16,  32, 64,  1, 2,   4,   16,  65,  4,   33,  0,   0, 0,   20,  35,  226, 20,  0,   0,
        0, 0,   8,   35,  226, 8,   0,  0,   0, 0,   0,   0,   2,   8,   64,  0,   0, 0,   0,   3,   224, 0,   0,   0,
        0, 0,   0,   0,   2,   8,   0,  0,   0, 33,  4,   32,  132, 16,  128, 0,   0, 0,   8,   32,  2,   8,   0,   0,
        0, 0,   8,   32,  2,   8,   64, 0,   0, 1,   8,   66,  4,   8,   16,  0,   0, 0,   0,   248, 15,  128, 0,   0,
        0, 4,   8,   16,  33,  8,   64, 0,   0, 7,   34,  16,  128, 8,   0,   0,   1, 200, 166, 170, 169, 160, 120, 0,
        1, 196, 16,  65,  4,   16,  65, 192, 2, 4,   16,  32,  129, 4,   8,   0,   1, 193, 4,   16,  65,  4,   17,  192,
        0, 130, 20,  82,  32,  0,   0,  0,   0, 0,   0,   0,   0,   0,   252, 0,   1, 2,   0,   0,   0,   0,   0,   0,
        0, 98,  8,   35,  2,   8,   32, 96,  0, 130, 8,   32,  130, 8,   32,  128, 3, 2,   8,   32,  98,  8,   35,  0,
        0, 0,   0,   74,  169, 0,   0,  0,   0, 0,   0,   0,   0,   0,   0,   0
    };
};
} // namespace epaperapi::fonts
