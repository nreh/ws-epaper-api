/**
 * This file was generated automatically using scripts/bitmapconversion/Bitmap2HeaderFile.py
 */

#pragma once

#include "AbstractBitmap.h"

#include <vector>

namespace epaperapi::bitmaps {
class Bluetooth : public AbstractBitmap {
  public:
    /// @brief Get the width of the bitmap in pixels
    uint16_t GetWidth() const override { return 14; }

    /// @brief Get the height of the bitmap in pixels
    uint16_t GetHeight() const override { return 17; }

    const uint8_t* GetBitmapData() const override { return bitmap.data(); }

  private:
    const std::vector<uint8_t> bitmap = {31,  224, 255, 199, 223, 191, 63,  252, 127, 148, 255, 25,  254, 79, 252,
                                         127, 228, 255, 25,  249, 79,  252, 127, 243, 247, 223, 143, 252, 31, 224};
};
} // namespace epaperapi::bitmaps
