/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 2.66inch e-Paper (G)
 * Shortname: EPD_2in66g
 * Generated On: 26 April 2025 @ 5:41 PM
 * Supported Color Channels: black,yellow,red
 * Type: Color2BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "2.66inch e-Paper (G)",
 *   "ScreenWidth": 184,
 *   "ScreenHeight": 360,
 *   "SupportedColorChannels": [
 *     "black",
 *     "yellow",
 *     "red"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_2IN66g_Init()"
 *     ],
 *     "Clear": [
 *       "EPD_2IN66g_Clear(UBYTE color)"
 *     ],
 *     "Display": [
 *       "EPD_2IN66g_Display(UBYTE *Image)"
 *     ],
 *     "Display_Base": [],
 *     "Display_Partial": [],
 *     "Display_Fast": [],
 *     "Display_Misc": [],
 *     "Sleep": [
 *       "EPD_2IN66g_Sleep()"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "The color definitions include 'black', 'yellow', and 'red'. 'White' is ignored as it falls under the
 * 'black' channel. Function categories are based on their name and expected purpose.",
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

/// @brief 2.66inch e-Paper (G)
namespace EPD_2in66g {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_2in66g.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 184;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 360;

enum RefreshMode { Display = 0 };

class EPD_2in66g_DrawTarget : public Color2BitEPD {
  public:
    std::string GetDeviceName() const override { return "2.66inch e-Paper (G)"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }
    
    /// @brief Initialize the display
    void Init() {
        controller::EPD_2IN66g_Init();
    }

    /// @brief Clear the display
    void Clear() {
        controller::EPD_2IN66g_Clear(0x1);
    }

    /// @brief Put the display to sleep
    void Sleep() {
        controller::EPD_2IN66g_Sleep();
    }

    /// @brief Display pixels in buffers to display
    void Display() {
        controller::EPD_2IN66g_Display(packedBits);
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

    EPD_2in66g_DrawTarget(bool initializeSPI = true) : Color2BitEPD(GetWidth(), GetHeight(), initializeSPI) {}
    ~EPD_2in66g_DrawTarget() {}
};

} // namespace EPD_2in66g

} // namespace devices

} // namespace epaperapi