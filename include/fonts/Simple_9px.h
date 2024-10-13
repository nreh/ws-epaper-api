/**
 * This file was generated automatically using scripts/fontmaking/Images2FontHeaders.py
 *
 * Font: Simple
 * Font Size: 9px
 * Generated On: 11 October 2024 @ 11:35 PM
 */

#pragma once

#include "AbstractFont.h"

#include <vector>

namespace epaperapi::fonts {
/// @brief A very simple uppercase alphabet and basic punctuation.
///
/// Note! Characterset only consists of LOWERCASE letters.
class Simple_9px : public AbstractFont {
  private:
    const std::string charset = "abcdefghijklmnopqrstuvwxyz_ .,?!";

  public:
    Simple_9px() {}
    uint8_t GetFontSize() const override { return 9; }
    uint8_t GetHeight() const override { return 9; }
    std::string GetFontName() override { return "Simple"; }
    std::string GetCharacterSet() const override { return charset; }
    const uint8_t* GetBitmapData() const override { return bitmap.data(); }
    const uint8_t* GetCharacterWidths() const override { return charWidths.data(); }

  private:
    const std::vector<uint8_t> charWidths = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 6, 5, 5,
                                             5, 5, 5, 5, 5, 5, 7, 5, 5, 5, 5, 5, 5, 5, 5, 5};

    const std::vector<uint8_t> bitmap = {
        116, 99,  31,  198, 49,  136, 244, 99,  31,  70,  49,  240, 124, 33,  8,   66,  16,  120, 228, 163, 24,  198,
        50,  224, 252, 33,  15,  66,  16,  248, 252, 33,  15,  66,  16,  128, 252, 33,  11,  198, 49,  248, 140, 99,
        31,  198, 49,  136, 249, 8,   66,  16,  132, 248, 248, 132, 33,  10,  82,  112, 140, 99,  46,  74,  49,  136,
        132, 33,  8,   66,  16,  248, 131, 143, 189, 217, 48,  96,  193, 130, 135, 28,  105, 166, 89,  99,  140, 116,
        99,  24,  198, 49,  112, 244, 99,  31,  66,  16,  128, 116, 99,  24,  198, 174, 24,  244, 99,  46,  74,  49,
        136, 124, 33,  7,   4,   33,  240, 249, 8,   66,  16,  132, 32,  140, 99,  24,  198, 49,  112, 140, 99,  21,
        41,  68,  32,  131, 6,   12,  25,  55,  123, 227, 130, 140, 84,  162, 41,  81,  136, 140, 98,  165, 16,  132,
        32,  248, 66,  34,  34,  16,  248, 255, 255, 255, 255, 255, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   4,   0,   0,   0,   0,   0,   4,   32,  116, 98,  17,  16,  128, 32,  33,  8,   66,  16,  128, 32
    };
};
} // namespace epaperapi::fonts
