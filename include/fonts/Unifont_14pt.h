/**
 * This file was generated automatically using scripts/fontmaking/Images2FontHeaders.py
 *
 * Font: Unifont
 * Font Size: 14pt
 * Generated On: 13 October 2024 @ 3:58 PM
 * License: https://unifoundry.com/LICENSE.txt
 */

#pragma once

#include "AbstractFont.h"

#include <vector>

namespace epaperapi::fonts {
class Unifont_14pt : public AbstractFont {
  private:
    const std::string charset =
        "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ ";

  public:
    Unifont_14pt() {}
    uint8_t GetFontSize() const override { return 14; }
    uint8_t GetHeight() const override { return 15; }
    std::string GetFontName() override { return "Unifont"; }
    std::string GetCharacterSet() const override { return charset; }
    const uint8_t* GetBitmapData() const override { return bitmap.data(); }
    const uint8_t* GetCharacterWidths() const override { return charWidths.data(); }

  private:
    const std::vector<uint8_t> charWidths = {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
                                             7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
                                             7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
                                             7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7};

    const std::vector<uint8_t> bitmap = {
        0,   0,   0,   1,   5,   17,  38,  84,  233, 17,  65,  0,   0,   0,   0,   0,   0,   1,   2,   12,  8,   16,  32,
        64,  131, 192, 0,   0,   0,   0,   0,   3,   136, 145, 2,   24,  97,  2,   7,   192, 0,   0,   0,   0,   0,   3,
        136, 145, 2,   24,  9,   18,  35,  128, 0,   0,   0,   0,   0,   0,   131, 6,   20,  72,  248, 32,  64,  128, 0,
        0,   0,   0,   0,   7,   200, 16,  32,  120, 8,   18,  35,  128, 0,   0,   0,   0,   0,   1,   132, 16,  32,  120,
        137, 18,  35,  128, 0,   0,   0,   0,   0,   7,   192, 129, 4,   8,   48,  64,  129, 0,   0,   0,   0,   0,   0,
        3,   136, 145, 34,  56,  137, 18,  35,  128, 0,   0,   0,   0,   0,   3,   136, 145, 34,  60,  8,   16,  67,  0,
        0,   0,   0,   0,   0,   0,   0,   14,  34,  4,   249, 18,  99,  64,  0,   0,   0,   0,   2,   4,   8,   22,  50,
        68,  137, 19,  37,  128, 0,   0,   0,   0,   0,   0,   0,   14,  34,  64,  129, 2,   35,  128, 0,   0,   0,   0,
        0,   32,  64,  141, 38,  68,  137, 18,  99,  64,  0,   0,   0,   0,   0,   0,   0,   14,  34,  68,  249, 2,   35,
        128, 0,   0,   0,   0,   0,   193, 2,   4,   60,  16,  32,  64,  129, 0,   0,   0,   0,   0,   0,   0,   0,   141,
        36,  72,  240, 129, 196, 72,  142, 0,   0,   0,   2,   4,   8,   22,  50,  68,  137, 18,  36,  64,  0,   0,   0,
        0,   0,   129, 0,   4,   8,   16,  32,  64,  131, 192, 0,   0,   0,   0,   0,   64,  128, 6,   4,   8,   16,  32,
        64,  138, 12,  0,   0,   0,   2,   4,   8,   18,  40,  80,  193, 66,  68,  64,  0,   0,   0,   0,   0,   129, 2,
        4,   8,   16,  32,  64,  131, 192, 0,   0,   0,   0,   0,   0,   0,   31,  41,  82,  165, 74,  149, 32,  0,   0,
        0,   0,   0,   0,   0,   22,  50,  68,  137, 18,  36,  64,  0,   0,   0,   0,   0,   0,   0,   14,  34,  68,  137,
        18,  35,  128, 0,   0,   0,   0,   0,   0,   0,   22,  50,  68,  137, 19,  37,  136, 16,  0,   0,   0,   0,   0,
        0,   13,  38,  68,  137, 18,  99,  64,  129, 0,   0,   0,   0,   0,   0,   22,  50,  68,  129, 2,   4,   0,   0,
        0,   0,   0,   0,   0,   0,   14,  34,  64,  112, 18,  35,  128, 0,   0,   0,   0,   0,   1,   2,   4,   60,  16,
        32,  64,  129, 128, 0,   0,   0,   0,   0,   0,   0,   17,  34,  68,  137, 18,  99,  64,  0,   0,   0,   0,   0,
        0,   0,   17,  34,  68,  80,  160, 129, 0,   0,   0,   0,   0,   0,   0,   0,   16,  169, 82,  165, 74,  147, 192,
        0,   0,   0,   0,   0,   0,   0,   17,  34,  40,  32,  162, 36,  64,  0,   0,   0,   0,   0,   0,   0,   17,  34,
        68,  136, 176, 160, 64,  142, 0,   0,   0,   0,   0,   0,   31,  2,   8,   32,  130, 7,   192, 0,   0,   0,   0,
        0,   1,   5,   10,  34,  68,  249, 18,  36,  64,  0,   0,   0,   0,   0,   7,   136, 145, 34,  120, 137, 18,  39,
        128, 0,   0,   0,   0,   0,   3,   136, 145, 32,  64,  129, 18,  35,  128, 0,   0,   0,   0,   0,   7,   9,   17,
        34,  68,  137, 18,  71,  0,   0,   0,   0,   0,   0,   7,   200, 16,  32,  120, 129, 2,   7,   192, 0,   0,   0,
        0,   0,   7,   200, 16,  32,  120, 129, 2,   4,   0,   0,   0,   0,   0,   0,   3,   136, 145, 32,  64,  185, 18,
        99,  64,  0,   0,   0,   0,   0,   4,   72,  145, 34,  124, 137, 18,  36,  64,  0,   0,   0,   0,   0,   3,   194,
        4,   8,   16,  32,  64,  131, 192, 0,   0,   0,   0,   0,   1,   225, 2,   4,   8,   17,  34,  67,  0,   0,   0,
        0,   0,   0,   4,   73,  20,  40,  96,  193, 66,  68,  64,  0,   0,   0,   0,   0,   4,   8,   16,  32,  64,  129,
        2,   7,   192, 0,   0,   0,   0,   0,   4,   72,  155, 54,  84,  169, 18,  36,  64,  0,   0,   0,   0,   0,   4,
        76,  153, 42,  84,  169, 50,  100, 64,  0,   0,   0,   0,   0,   3,   136, 145, 34,  68,  137, 18,  35,  128, 0,
        0,   0,   0,   0,   7,   136, 145, 34,  120, 129, 2,   4,   0,   0,   0,   0,   0,   0,   3,   136, 145, 34,  68,
        137, 83,  99,  128, 192, 0,   0,   0,   0,   7,   136, 145, 34,  120, 161, 34,  36,  64,  0,   0,   0,   0,   0,
        3,   136, 145, 32,  48,  17,  18,  35,  128, 0,   0,   0,   0,   0,   7,   226, 4,   8,   16,  32,  64,  129, 0,
        0,   0,   0,   0,   0,   4,   72,  145, 34,  68,  137, 18,  35,  128, 0,   0,   0,   0,   0,   4,   40,  80,  146,
        36,  88,  96,  129, 0,   0,   0,   0,   0,   0,   4,   72,  145, 34,  84,  233, 178, 36,  64,  0,   0,   0,   0,
        0,   4,   72,  138, 20,  16,  96,  162, 36,  64,  0,   0,   0,   0,   0,   4,   40,  73,  18,  24,  32,  64,  129,
        0,   0,   0,   0,   0,   0,   7,   192, 129, 4,   16,  97,  2,   7,   192, 0,   0,   0,   0,   0,   1,   2,   4,
        8,   16,  32,  0,   129, 0,   0,   0,   0,   0,   145, 34,  68,  128, 0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   1,   66,  133, 62,  40,  217, 66,  133, 0,   0,   0,   0,   0,   0,   1,   7,   148, 168, 48,  61,  73,
        225, 0,   0,   0,   0,   0,   0,   3,   42,  149, 28,  16,  56,  201, 148, 192, 0,   0,   0,   0,   0,   1,   132,
        137, 12,  16,  245, 18,  99,  32,  0,   0,   0,   0,   64,  129, 2,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   65,  2,   4,   8,   16,  32,  64,  129, 1,   0,   0,   0,   0,   1,   1,   2,   4,   8,   16,  32,
        64,  129, 4,   0,   0,   0,   0,   0,   0,   0,   4,   41,  52,  121, 72,  128, 0,   0,   0,   0,   0,   0,   0,
        0,   4,   8,   16,  252, 64,  128, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   129, 2,   4,
        0,   0,   0,   0,   0,   0,   0,   0,   56,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   129, 0,   0,   0,   0,   0,   0,   0,   64,  130, 8,   16,  32,  130, 4,   0,   0,   0,   0,   0,   0,
        0,   0,   4,   8,   0,   0,   64,  128, 0,   0,   0,   0,   0,   0,   0,   0,   4,   8,   0,   0,   64,  129, 2,
        0,   0,   0,   0,   0,   0,   0,   130, 8,   16,  64,  64,  64,  64,  0,   0,   0,   0,   0,   0,   0,   31,  0,
        0,   248, 0,   0,   0,   0,   0,   0,   0,   0,   0,   8,   8,   8,   16,  48,  65,  4,   0,   0,   0,   0,   0,
        0,   3,   136, 145, 2,   8,   32,  0,   129, 0,   0,   0,   0,   0,   0,   1,   132, 149, 46,  84,  169, 113, 1,
        192, 0,   0,   0,   0,   0,   225, 2,   4,   8,   16,  32,  64,  129, 3,   128, 0,   0,   0,   0,   4,   8,   8,
        8,   16,  32,  32,  32,  64,  0,   0,   0,   0,   3,   129, 2,   4,   8,   16,  32,  64,  129, 14,  0,   0,   0,
        0,   65,  68,  64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   15,  192, 0,   0,   64,  64,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   193, 2,
        4,   8,   16,  96,  64,  129, 2,   6,   0,   0,   0,   64,  129, 2,   4,   8,   16,  32,  64,  129, 2,   4,   0,
        0,   0,   1,   129, 2,   4,   8,   16,  48,  64,  129, 2,   12,  0,   0,   0,   1,   149, 41,  128, 0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0
    };
};
} // namespace epaperapi::fonts
