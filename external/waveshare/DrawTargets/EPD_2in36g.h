/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 2.36inch e-Paper (G)
 * Shortname: EPD_2in36g
 * Generated On: 26 April 2025 @ 5:41 PM
 * Supported Color Channels: black,yellow,red
 * Type: Color2BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "2.36inch e-Paper (G)",
 *   "ScreenWidth": 168,
 *   "ScreenHeight": 296,
 *   "SupportedColorChannels": [
 *     "black",
 *     "yellow",
 *     "red"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_2IN36G_Init()"
 *     ],
 *     "Clear": [
 *       "EPD_2IN36G_Clear(UBYTE color)"
 *     ],
 *     "Display": [
 *       "EPD_2IN36G_Display(UBYTE *Image)"
 *     ],
 *     "Display_Base": [],
 *     "Display_Partial": [],
 *     "Display_Fast": [],
 *     "Display_Misc": [],
 *     "Sleep": [
 *       "EPD_2IN36G_Sleep()"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "The color definitions include 'black', 'yellow', and 'red'. 'White' is ignored as it falls under the
 * 'black' channel. Functions are categorized based on their names and expected behaviors.",
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

/// @brief 2.36inch e-Paper (G)
namespace EPD_2in36g {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_2in36g.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 168;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 296;

enum RefreshMode { Display = 0 };

class EPD_2in36g_DrawTarget : public Color2BitEPD {
  public:
    std::string GetDeviceName() const override { return "2.36inch e-Paper (G)"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }

    /// @brief Initialize the display
    void Init() { controller::EPD_2IN36G_Init(); }

    /// @brief Clear the display
    void Clear() { controller::EPD_2IN36G_Clear(0x1); }

    /// @brief Put the display to sleep
    void Sleep() { controller::EPD_2IN36G_Sleep(); }

    /// @brief Display pixels in buffers to display
    void Display() { controller::EPD_2IN36G_Display(packedBits); }

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

    EPD_2in36g_DrawTarget(bool initialize = true) : Color2BitEPD(GetWidth(), GetHeight(), initialize) {
        if (initialize)
            Init();
    }
    ~EPD_2in36g_DrawTarget() {}
};

} // namespace EPD_2in36g

} // namespace devices

} // namespace epaperapi