/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 1.54inch DES e-paper V1.0
 * Shortname: EPD_1in54_DES
 * Generated On: 26 April 2025 @ 5:06 PM
 * Supported Color Channels: black
 * Type: Black1BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "1.54inch DES e-paper V1.0",
 *   "ScreenWidth": 152,
 *   "ScreenHeight": 152,
 *   "SupportedColorChannels": [
 *     "black"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_1IN54_DES_Init(void)"
 *     ],
 *     "Clear": [
 *       "EPD_1IN54_DES_Clear(void)"
 *     ],
 *     "Display": [
 *       "EPD_1IN54_DES_Display(UBYTE *Image)"
 *     ],
 *     "Display_Base": [],
 *     "Display_Partial": [],
 *     "Display_Fast": [],
 *     "Display_Misc": [],
 *     "Sleep": [
 *       "EPD_1IN54_DES_Sleep(void)"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "Only one color channel (UBYTE *Image) is used in the EPD_1IN54_DES_Display function, so 'black' is
 * assumed. Functions are clearly named, so categorization was straightforward.",
 *   "PaintRotation": 90,
 *   "BitmapFunction": "GUI_ReadBmp"
 * }
 */
 
#pragma once

#include "../EPD_Common.h"

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief 1.54inch DES e-paper V1.0
namespace EPD_1in54_DES {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_1in54_DES.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 152;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 152;

enum RefreshMode { Display = 0 };

class EPD_1in54_DES_DrawTarget : public Black1BitEPD {
  public:
    std::string GetDeviceName() const override { return "1.54inch DES e-paper V1.0"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }
    
    /// @brief Initialize the display
    void Init() {
        controller::EPD_1IN54_DES_Init();
    }

    /// @brief Clear the display
    void Clear() {
        controller::EPD_1IN54_DES_Clear();
    }

    /// @brief Put the display to sleep
    void Sleep() {
        controller::EPD_1IN54_DES_Sleep();
    }

    /// @brief Display pixels in buffers to display
    void Display() {
        controller::EPD_1IN54_DES_Display(packedBits);
    }

    /// @brief Refresh the display with current buffer
    /// @param mode How to refresh the display
    void Refresh(int mode) override {
        if (!IsOpen()) {
            throw RefreshingClosedDevice(GetDeviceName());
        }

        PreprocessBuffers();

        switch (static_cast<RefreshMode>(mode)) {
        case RefreshMode::Display:
        Display();
        break;


        default:
            throw UnsupportedRefreshMode(mode, GetDeviceName());
        }
        
    }

    EPD_1in54_DES_DrawTarget(bool initializeSPI = true) : Black1BitEPD(GetWidth(), GetHeight(), initializeSPI) {}
    ~EPD_1in54_DES_DrawTarget() {}
};

} // namespace EPD_1in54_DES

} // namespace devices

} // namespace epaperapi