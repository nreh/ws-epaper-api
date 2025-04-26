/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 7.3inch e-Paper (F) Driver
 * Shortname: EPD_7in3f
 * Generated On: 26 April 2025 @ 5:41 PM
 * Supported Color Channels: black,red,green,blue,yellow,orange
 * Type: _7Color4BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "7.3inch e-Paper (F) Driver",
 *   "ScreenWidth": 800,
 *   "ScreenHeight": 480,
 *   "SupportedColorChannels": [
 *     "black",
 *     "red",
 *     "green",
 *     "blue",
 *     "yellow",
 *     "orange"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_7IN3F_Init(void)"
 *     ],
 *     "Clear": [
 *       "EPD_7IN3F_Clear(UBYTE color)"
 *     ],
 *     "Display": [
 *       "EPD_7IN3F_Display(UBYTE *Image)"
 *     ],
 *     "Display_Base": [],
 *     "Display_Partial": [],
 *     "Display_Fast": [],
 *     "Display_Misc": [
 *       "EPD_7IN3F_Show7Block(void)"
 *     ],
 *     "Sleep": [
 *       "EPD_7IN3F_Sleep(void)"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "The SupportedColorChannels include black, red, green, blue, yellow, and orange as defined by the color
 * index. WHITE and CLEAN are ignored, given part of the guidelines to only consider black as the primary channel for
 * those cases.",
 *   "PaintScale": 7,
 *   "PaintRotation": 0,
 *   "BitmapFunction": "GUI_ReadBmp_RGB_7Color"
 * }
 */

#pragma once

#include "../EPD_Common.h"

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief 7.3inch e-Paper (F) Driver
namespace EPD_7in3f {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_7in3f.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 800;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 480;

enum RefreshMode { Display = 0, Display2 = 1 };

class EPD_7in3f_DrawTarget : public _7Color4BitEPD {
  public:
    std::string GetDeviceName() const override { return "7.3inch e-Paper (F) Driver"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }

    /// @brief Initialize the display
    void Init() { controller::EPD_7IN3F_Init(); }

    /// @brief Clear the display
    void Clear() { controller::EPD_7IN3F_Clear(0x1); }

    /// @brief Put the display to sleep
    void Sleep() { controller::EPD_7IN3F_Sleep(); }

    /// @brief Display pixels in buffers to display
    void Display() { controller::EPD_7IN3F_Show7Block(); }

    /// @brief Display pixels in buffers to display
    void Display2() { controller::EPD_7IN3F_Display(packedBits); }

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

        case RefreshMode::Display2:
            Display2();
            break;

        default:
            throw UnsupportedRefreshMode(mode, GetDeviceName());
        }
    }

    EPD_7in3f_DrawTarget(bool initializeSPI = true) : _7Color4BitEPD(GetWidth(), GetHeight(), initializeSPI) {}
    ~EPD_7in3f_DrawTarget() {}
};

} // namespace EPD_7in3f

} // namespace devices

} // namespace epaperapi