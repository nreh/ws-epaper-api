/**
 * This file was generated automatically using scripts/bitmapconversion/Bitmap2HeaderFile.py
 */

#pragma once

#include "AbstractBitmap.h"

#include <vector>

namespace epaperapi::bitmaps {
class Cross : public AbstractBitmap {
  public:
    /// @brief Get the width of the bitmap in pixels
    uint16_t GetWidth() const override { return 23; }

    /// @brief Get the height of the bitmap in pixels
    uint16_t GetHeight() const override { return 23; }

    const uint8_t* GetBitmapData() const override { return bitmap.data(); }

  private:
    const std::vector<uint8_t> bitmap = {16,  0,   16,  112, 0,   113, 240, 1,   247, 240, 7,   247, 240, 31,  199, 240, 127,
                                         7,   241, 252, 7,   247, 240, 7,   255, 192, 7,   255, 0,   7,   252, 0,   7,   240,
                                         0,   31,  240, 0,   127, 240, 1,   255, 240, 7,   247, 240, 31,  199, 240, 127, 7,
                                         241, 252, 7,   247, 240, 7,   247, 192, 7,   199, 0,   7,   4,   0,   4,   0};
};
} // namespace epaperapi::bitmaps
