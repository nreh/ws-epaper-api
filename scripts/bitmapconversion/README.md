# 🪄 Bitmap Conversion

This folder contains a script for converting bitmaps to C++ headerfiles that can be used to render images using
[`BitmapElement`](../../include/elements/BitmapElement.h)

## 🖼️ Step 1: Create Bitmap

Use a photo editing sofware to create and save a .bmp file in **1-Bit format**. Otherwise, the image will not be able to be
processed by the script.

## 📃 Step 2: Convert to Header Files

Use the **Bitmap2HeaderFile.py** script to generate a header file for the desired image file.

## ✏️ Step 3: Rename Headerfile & Class

In the generated headerfile will look something like this:

```cpp
/**
 * This file was generated automatically using scripts/bitmapconversion/Bitmap2HeaderFile.py
 */

#pragma once

#include "AbstractBitmap.h"

#include <vector>

namespace epaperapi::bitmaps {
class TestBitmap : public AbstractBitmap {
  public:
    /// @brief Get the width of the bitmap in pixels
    uint16_t GetWidth() const override { return 50; }

    /// @brief Get the height of the bitmap in pixels
    uint16_t GetHeight() const override { return 50; }

    const uint8_t* GetBitmapData() const override { return bitmap.data(); }

  private:
    const std::vector<uint8_t> bitmap = {
        // your image data...
    };
};
} // namespace epaperapi::bitmaps

```

You need to rename the file to something describing the image and the same for the classname (currently `TestBitmap`)

Now you can move the generated header file into your include directory and use it in `BitmapElement`!

```cpp
// Example using 'Wifi' bitmap
auto wifiLogo = epaperapi::bitmaps::Wifi();
BitmapElement bmpElem(0, 0, wifiLogo);
```

## 💡 Tips

- Sometimes when converting, images will be rendered in inverted colors. To fix this, re-run the script using the `--invert`
  flag.
