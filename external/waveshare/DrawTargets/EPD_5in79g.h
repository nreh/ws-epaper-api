/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: EPD 5.79 inch g
 * Shortname: EPD_5in79g
 * Generated On: 27 January 2025 @ 2:59 AM
 * Supported Color Channels: black,yellow,red
 * Type: Color2BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "EPD 5.79 inch g",
 *   "ScreenWidth": 792,
 *   "ScreenHeight": 272,
 *   "SupportedColorChannels": [
 *     "black",
 *     "yellow",
 *     "red"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_5in79g_Init(void)"
 *     ],
 *     "Clear": [
 *       "EPD_5in79g_Clear(UBYTE color)"
 *     ],
 *     "Display": [
 *       "EPD_5in79g_Display(const UBYTE *Image)"
 *     ],
 *     "Display_Base": [],
 *     "Display_Partial": [],
 *     "Display_Fast": [],
 *     "Display_Misc": [
 *       "EPD_5in79g_Show(void)"
 *     ],
 *     "Sleep": [
 *       "EPD_5in79g_Sleep(void)"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "'black', 'yellow', and 'red' color channels are supported as indicated by the defined colors. The
 * presence of 'white' is ignored based on the instructions, as it's managed within 'black'. 'EPD_5in79g_Show' was
 * categorized under Display_Misc, as it may relate to display functions but specifics are unclear.",
 *   "PaintScale": 4,
 *   "PaintRotation": 180,
 *   "BitmapFunction": "GUI_ReadBmp_RGB_4Color"
 * }
 */
 
#pragma once

#include "../EPD_Common.h"

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief EPD 5.79 inch g
namespace EPD_5in79g {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_5in79g.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 792;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 272;

enum RefreshMode { Display = 0, Display = 1 };

class EPD_5in79g_DrawTarget : public Color2BitEPD {
  public:
    std::string GetDeviceName() const override { return "EPD 5.79 inch g"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }
    
    // The following functions were not created:

    //  ! EPD_5in79g_Clear(UBYTE color) was skipped because I'm not sure what arguments to pass in!

    /// @brief Initialize the display
    void Init() {
        controller::EPD_5in79g_Init();
    }

    /// @brief Put the display to sleep
    void Sleep() {
        controller::EPD_5in79g_Sleep();
    }

    /// @brief Display pixels in buffers to display
    void Display() {
        controller::EPD_5in79g_Show();
    }

    /// @brief Display pixels in buffers to display
    void Display() {
        controller::EPD_5in79g_Display(packedBits);
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

        case RefreshMode::Display:
        Display();
        break;


        default:
            throw UnsupportedRefreshMode(mode, GetDeviceName());
        }
        
    }

    EPD_5in79g_DrawTarget() : Color2BitEPD(GetWidth(), GetHeight()) {}
    ~EPD_5in79g_DrawTarget() {}
};

} // namespace EPD_5in79g

} // namespace devices

} // namespace epaperapi