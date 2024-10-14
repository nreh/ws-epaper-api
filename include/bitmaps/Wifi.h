/**
 * This file was generated automatically using scripts/bitmapconversion/Bitmap2HeaderFiles.py
 */

#pragma once

#include "AbstractBitmap.h"

#include <vector>

namespace epaperapi::bitmaps {
class Wifi : public AbstractBitmap {
  public:
    /// @brief Get the width of the bitmap in pixels
    uint16_t GetWidth() const override { return 22; }

    /// @brief Get the height of the bitmap in pixels
    uint16_t GetHeight() const override { return 15; }

    const uint8_t* GetBitmapData() const override { return bitmap.data(); }

  private:
    const std::vector<uint8_t> bitmap = {0,   120, 0,   7,   248, 0,   63,  240, 15,  255, 252, 127, 248, 11,
                                         186, 206, 158, 239, 32,  122, 172, 201, 234, 178, 39,  214, 200, 151,
                                         254, 0,   143, 255, 252, 3,   255, 0,   7,   248, 0,   7,   128, 0};
};
} // namespace epaperapi::bitmaps
