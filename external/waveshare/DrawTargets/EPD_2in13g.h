/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 2.13inch e-paper G
 * Shortname: EPD_2in13g
 * Generated On: 27 January 2025 @ 2:59 AM
 * Supported Color Channels: black,yellow,red
 * Type: Color2BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "2.13inch e-paper G",
 *   "ScreenWidth": 122,
 *   "ScreenHeight": 250,
 *   "SupportedColorChannels": [
 *     "black",
 *     "yellow",
 *     "red"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_2IN13G_Init()"
 *     ],
 *     "Clear": [
 *       "EPD_2IN13G_Clear(UBYTE color)"
 *     ],
 *     "Display": [
 *       "EPD_2IN13G_Display(UBYTE *Image)"
 *     ],
 *     "Display_Base": [],
 *     "Display_Partial": [],
 *     "Display_Fast": [],
 *     "Display_Misc": [],
 *     "Sleep": [
 *       "EPD_2IN13G_Sleep()"
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

/// @brief 2.13inch e-paper G
namespace EPD_2in13g {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_2in13g.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 122;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 250;

enum RefreshMode { Display = 0 };

class EPD_2in13g_DrawTarget : public Color2BitEPD {
  public:
    std::string GetDeviceName() const override { return "2.13inch e-paper G"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }
    
    // The following functions were not created:

    //  ! EPD_2IN13G_Clear(UBYTE color) was skipped because I'm not sure what arguments to pass in!

    /// @brief Initialize the display
    void Init() {
        controller::EPD_2IN13G_Init();
    }

    /// @brief Put the display to sleep
    void Sleep() {
        controller::EPD_2IN13G_Sleep();
    }

    /// @brief Display pixels in buffers to display
    void Display() {
        controller::EPD_2IN13G_Display(packedBits);
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

    EPD_2in13g_DrawTarget() : Color2BitEPD(GetWidth(), GetHeight()) {}
    ~EPD_2in13g_DrawTarget() {}
};

} // namespace EPD_2in13g

} // namespace devices

} // namespace epaperapi