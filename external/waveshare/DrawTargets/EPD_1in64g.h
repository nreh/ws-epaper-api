/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 1.64inch e-paper(G)
 * Shortname: EPD_1in64g
 * Generated On: 27 January 2025 @ 5:09 AM
 * Supported Color Channels: black,yellow,red
 * Type: Color2BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "1.64inch e-paper(G)",
 *   "ScreenWidth": 168,
 *   "ScreenHeight": 168,
 *   "SupportedColorChannels": [
 *     "black",
 *     "yellow",
 *     "red"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_1IN64G_Init()"
 *     ],
 *     "Clear": [
 *       "EPD_1IN64G_Clear(UBYTE color)"
 *     ],
 *     "Display": [
 *       "EPD_1IN64G_Display(UBYTE *Image)"
 *     ],
 *     "Display_Base": [],
 *     "Display_Partial": [],
 *     "Display_Fast": [],
 *     "Display_Misc": [],
 *     "Sleep": [
 *       "EPD_1IN64G_Sleep()"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "The color definitions suggest support for 'black', 'yellow', and 'red'. The 'white' color is ignored
 * since it's considered part of the 'black' channel. Function categorization is based on their straightforward
 * naming.",
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

/// @brief 1.64inch e-paper(G)
namespace EPD_1in64g {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_1in64g.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 168;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 168;

enum RefreshMode { Display = 0 };

class EPD_1in64g_DrawTarget : public Color2BitEPD {
  public:
    std::string GetDeviceName() const override { return "1.64inch e-paper(G)"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }
    
    // The following functions were not created:

    //  ! EPD_1IN64G_Clear(UBYTE color) was skipped because I'm not sure what arguments to pass in!

    /// @brief Initialize the display
    void Init() {
        controller::EPD_1IN64G_Init();
    }

    /// @brief Put the display to sleep
    void Sleep() {
        controller::EPD_1IN64G_Sleep();
    }

    /// @brief Display pixels in buffers to display
    void Display() {
        controller::EPD_1IN64G_Display(packedBits);
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

    EPD_1in64g_DrawTarget(bool initializeSPI = true) : Color2BitEPD(GetWidth(), GetHeight(), initializeSPI) {}
    ~EPD_1in64g_DrawTarget() {}
};

} // namespace EPD_1in64g

} // namespace devices

} // namespace epaperapi