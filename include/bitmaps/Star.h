/**
 * This file was generated automatically using scripts/bitmapconversion/Bitmap2HeaderFile.py
 */

#pragma once

#include "AbstractBitmap.h"

#include <vector>

namespace epaperapi::bitmaps {
class Star : public AbstractBitmap {
  public:
    /// @brief Get the width of the bitmap in pixels
    uint16_t GetWidth() const override { return 23; }

    /// @brief Get the height of the bitmap in pixels
    uint16_t GetHeight() const override { return 23; }

    const uint8_t* GetBitmapData() const override { return bitmap.data(); }

  private:
    const std::vector<uint8_t> bitmap = {0,   16,  0,   0,   112, 0,   0,   224, 0,   3,   224, 0,   7,   192, 0,   15,  128,
                                         0,   63,  128, 0,   127, 0,   255, 255, 254, 255, 255, 248, 255, 255, 224, 255, 255,
                                         128, 255, 254, 0,   255, 248, 0,   255, 224, 1,   255, 192, 7,   255, 192, 15,  255,
                                         128, 63,  191, 128, 126, 63,  1,   248, 63,  3,   224, 62,  7,   0,   28,  0};
};
} // namespace epaperapi::bitmaps
