/**
 * This file was generated automatically using scripts/bitmapconversion/Bitmap2HeaderFile.py
 */

#pragma once

#include "AbstractBitmap.h"

#include <vector>

namespace epaperapi::bitmaps {
class Gear : public AbstractBitmap {
  public:
    /// @brief Get the width of the bitmap in pixels
    uint16_t GetWidth() const override { return 25; }

    /// @brief Get the height of the bitmap in pixels
    uint16_t GetHeight() const override { return 25; }

    const uint8_t* GetBitmapData() const override { return bitmap.data(); }

  private:
    const std::vector<uint8_t> bitmap = {0,   28,  0,   0,   31,  0,   0,   15,  128, 1,   207, 231, 1,   255, 255, 192,
                                         255, 255, 224, 127, 255, 240, 31,  255, 240, 15,  193, 248, 15,  192, 126, 31,
                                         192, 31,  223, 224, 15,  255, 240, 7,   255, 248, 3,   253, 252, 1,   252, 63,
                                         1,   248, 15,  193, 248, 7,   255, 252, 7,   255, 255, 3,   255, 255, 129, 255,
                                         255, 192, 115, 249, 192, 0,   248, 0,   0,   124, 0,   0,   28,  0,   0};
};
} // namespace epaperapi::bitmaps
