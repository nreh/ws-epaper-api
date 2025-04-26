/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 7.3inchg e-paper G
 * Shortname: EPD_7in3g
 * Generated On: 26 April 2025 @ 5:41 PM
 * Supported Color Channels: black,yellow,red
 * Type: Color2BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "7.3inchg e-paper G",
 *   "ScreenWidth": 800,
 *   "ScreenHeight": 480,
 *   "SupportedColorChannels": [
 *     "black",
 *     "yellow",
 *     "red"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_7IN3G_Init()"
 *     ],
 *     "Clear": [
 *       "EPD_7IN3G_Clear(UBYTE color)"
 *     ],
 *     "Display": [
 *       "EPD_7IN3G_Display(UBYTE *Image)"
 *     ],
 *     "Display_Base": [],
 *     "Display_Partial": [],
 *     "Display_Fast": [],
 *     "Display_Misc": [],
 *     "Sleep": [
 *       "EPD_7IN3G_Sleep()"
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

/// @brief 7.3inchg e-paper G
namespace EPD_7in3g {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_7in3g.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 800;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 480;

enum RefreshMode { Display = 0 };

class EPD_7in3g_DrawTarget : public Color2BitEPD {
  public:
    std::string GetDeviceName() const override { return "7.3inchg e-paper G"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }
    
    /// @brief Initialize the display
    void Init() {
        controller::EPD_7IN3G_Init();
    }

    /// @brief Clear the display
    void Clear() {
        controller::EPD_7IN3G_Clear(0x1);
    }

    /// @brief Put the display to sleep
    void Sleep() {
        controller::EPD_7IN3G_Sleep();
    }

    /// @brief Display pixels in buffers to display
    void Display() {
        controller::EPD_7IN3G_Display(packedBits);
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

    EPD_7in3g_DrawTarget(bool initializeSPI = true) : Color2BitEPD(GetWidth(), GetHeight(), initializeSPI) {}
    ~EPD_7in3g_DrawTarget() {}
};

} // namespace EPD_7in3g

} // namespace devices

} // namespace epaperapi