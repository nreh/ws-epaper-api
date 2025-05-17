/**
 * This file was generated automatically using scripts/bitmapconversion/Bitmap2HeaderFile.py
 */

#pragma once

#include "AbstractBitmap.h"

#include <vector>

namespace epaperapi::bitmaps {
class Check : public AbstractBitmap {
  public:
    /// @brief Get the width of the bitmap in pixels
    uint16_t GetWidth() const override { return 23; }

    /// @brief Get the height of the bitmap in pixels
    uint16_t GetHeight() const override { return 23; }

    const uint8_t* GetBitmapData() const override { return bitmap.data(); }

  private:
    const std::vector<uint8_t> bitmap = {0,   0,   16,  0,  0,   112, 0,  0,   240, 0,  3,   240, 0,  15,  192, 0,   31,
                                         128, 0,   126, 0,  1,   248, 0,  7,   224, 0,  15,  192, 0,  63,  0,   128, 252,
                                         3,   131, 240, 15, 135, 224, 63, 159, 128, 63, 254, 0,   63, 248, 0,   63,  240,
                                         0,   63,  192, 0,  63,  0,   0,  60,  0,   0,  56,  0,   0,  32,  0,   0};
};
} // namespace epaperapi::bitmaps
