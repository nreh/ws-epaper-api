/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 3inch e-paper G
 * Shortname: EPD_3in0g
 * Generated On: 26 April 2025 @ 5:41 PM
 * Supported Color Channels: black,yellow,red
 * Type: Color2BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "3inch e-paper G",
 *   "ScreenWidth": 168,
 *   "ScreenHeight": 400,
 *   "SupportedColorChannels": [
 *     "black",
 *     "yellow",
 *     "red"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_3IN0G_Init()"
 *     ],
 *     "Clear": [
 *       "EPD_3IN0G_Clear(UBYTE color)"
 *     ],
 *     "Display": [
 *       "EPD_3IN0G_Display(UBYTE *Image)"
 *     ],
 *     "Display_Base": [],
 *     "Display_Partial": [],
 *     "Display_Fast": [],
 *     "Display_Misc": [],
 *     "Sleep": [
 *       "EPD_3IN0G_Sleep()"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "The header defines colors BLACK, WHITE, YELLOW, and RED. WHITE is covered by the 'black' channel, so it
 * is not included separately. Functions were categorized based on typical e-paper operations.",
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

/// @brief 3inch e-paper G
namespace EPD_3in0g {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_3in0g.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 168;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 400;

enum RefreshMode { Display = 0 };

class EPD_3in0g_DrawTarget : public Color2BitEPD {
  public:
    std::string GetDeviceName() const override { return "3inch e-paper G"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }

    /// @brief Initialize the display
    void Init() { controller::EPD_3IN0G_Init(); }

    /// @brief Clear the display
    void Clear() { controller::EPD_3IN0G_Clear(0x1); }

    /// @brief Put the display to sleep
    void Sleep() { controller::EPD_3IN0G_Sleep(); }

    /// @brief Display pixels in buffers to display
    void Display() { controller::EPD_3IN0G_Display(packedBits); }

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

    EPD_3in0g_DrawTarget(bool initialize = true) : Color2BitEPD(GetWidth(), GetHeight(), initialize) {
        if (initialize)
            Init();
    }
    ~EPD_3in0g_DrawTarget() {}
};

} // namespace EPD_3in0g

} // namespace devices

} // namespace epaperapi