/**
 * This file was generated automatically using scripts/bitmapconversion/Bitmap2HeaderFile.py
 */

#pragma once

#include "AbstractBitmap.h"

#include <vector>

namespace epaperapi::bitmaps {
class Lightning : public AbstractBitmap {
  public:
    /// @brief Get the width of the bitmap in pixels
    uint16_t GetWidth() const override { return 23; }

    /// @brief Get the height of the bitmap in pixels
    uint16_t GetHeight() const override { return 23; }

    const uint8_t* GetBitmapData() const override { return bitmap.data(); }

  private:
    const std::vector<uint8_t> bitmap = {1,   128, 0,   15,  0,   0,   127, 0,   3,   255, 0,   15,  255, 0,   15,  254, 0,
                                         7,   254, 0,   3,   248, 0,   1,   248, 0,   7,   248, 0,   31,  248, 0,   15,  248,
                                         0,   15,  248, 0,   7,   224, 0,   3,   192, 0,   15,  192, 0,   31,  192, 0,   15,
                                         192, 0,   7,   128, 0,   3,   128, 0,   3,   128, 0,   1,   128, 0,   0,   128};
};
} // namespace epaperapi::bitmaps
