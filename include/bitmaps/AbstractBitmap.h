#pragma once

#include <stdint.h>

namespace epaperapi::bitmaps {

/// @brief A bitmap image that can be drawn using `Bitmap1BitElement`
class AbstractBitmap {
  public:
    /// @brief Get bitmap width in pixels
    virtual uint16_t GetWidth() const = 0;

    /// @brief Get bitmap height in pixels
    virtual uint16_t GetHeight() const = 0;

    /// @brief Get pointer to array containing bitmap data
    virtual const uint8_t* GetBitmapData() const = 0;
};

} // namespace epaperapi