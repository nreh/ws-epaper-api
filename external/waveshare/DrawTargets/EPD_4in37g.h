/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 4.37inch e-Paper G V1.0
 * Shortname: EPD_4in37g
 * Generated On: 26 April 2025 @ 5:41 PM
 * Supported Color Channels: black,red,yellow
 * Type: Color2BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "4.37inch e-Paper G V1.0",
 *   "ScreenWidth": 512,
 *   "ScreenHeight": 368,
 *   "SupportedColorChannels": [
 *     "black",
 *     "red",
 *     "yellow"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_4IN37G_Init(void)"
 *     ],
 *     "Clear": [
 *       "EPD_4IN37G_Clear(UBYTE color)"
 *     ],
 *     "Display": [
 *       "EPD_4IN37G_Display(UBYTE *Image)"
 *     ],
 *     "Display_Base": [],
 *     "Display_Partial": [],
 *     "Display_Fast": [],
 *     "Display_Misc": [],
 *     "Sleep": [
 *       "EPD_4IN37G_Sleep(void)"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "The supported colors black, red, and yellow are derived from the defined color constants. The function
 * names correspond clearly to their purpose and can be categorized accordingly.",
 *   "PaintScale": 4,
 *   "PaintRotation": 0,
 *   "BitmapFunction": "GUI_ReadBmp_RGB_4Color"
 * }
 */

#pragma once

#include "../EPD_Common.h"

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief 4.37inch e-Paper G V1.0
namespace EPD_4in37g {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_4in37g.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 512;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 368;

enum RefreshMode { Display = 0 };

class EPD_4in37g_DrawTarget : public Color2BitEPD {
  public:
    std::string GetDeviceName() const override { return "4.37inch e-Paper G V1.0"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }

    /// @brief Initialize the display
    void Init() { controller::EPD_4IN37G_Init(); }

    /// @brief Clear the display
    void Clear() { controller::EPD_4IN37G_Clear(0x1); }

    /// @brief Put the display to sleep
    void Sleep() { controller::EPD_4IN37G_Sleep(); }

    /// @brief Display pixels in buffers to display
    void Display() { controller::EPD_4IN37G_Display(packedBits); }

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

    EPD_4in37g_DrawTarget(bool initializeSPI = true) : Color2BitEPD(GetWidth(), GetHeight(), initializeSPI) {}
    ~EPD_4in37g_DrawTarget() {}
};

} // namespace EPD_4in37g

} // namespace devices

} // namespace epaperapi