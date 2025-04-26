/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 7.3inch e-Paper (F)
 * Shortname: EPD_7in3e
 * Generated On: 26 April 2025 @ 5:06 PM
 * Supported Color Channels: black,red,yellow,blue,green
 * Type: _6Color4BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "7.3inch e-Paper (F)",
 *   "ScreenWidth": 800,
 *   "ScreenHeight": 480,
 *   "SupportedColorChannels": [
 *     "black",
 *     "red",
 *     "yellow",
 *     "blue",
 *     "green"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_7IN3E_Init()",
 *       "EPD_7IN3E_Init_Fast()"
 *     ],
 *     "Clear": [
 *       "EPD_7IN3E_Clear(UBYTE color)"
 *     ],
 *     "Display": [
 *       "EPD_7IN3E_Display(UBYTE *Image)"
 *     ],
 *     "Display_Base": [],
 *     "Display_Partial": [],
 *     "Display_Fast": [],
 *     "Display_Misc": [
 *       "EPD_7IN3E_Show()",
 *       "EPD_7IN3E_Show7Block()"
 *     ],
 *     "Sleep": [
 *       "EPD_7IN3E_Sleep()"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "The supported color channels are explicitly defined with indices for black, yellow, red, blue, and green,
 * indicating these colors are supported by the display. The function EPD_7IN3E_Show7Block() and EPD_7IN3E_Show() are
 * considered Display_Misc due to lack of clarity on their specific purpose.",
 *   "PaintScale": 6,
 *   "PaintRotation": 0,
 *   "BitmapFunction": "GUI_ReadBmp_RGB_6Color"
 * }
 */
 
#pragma once

#include "../EPD_Common.h"

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief 7.3inch e-Paper (F)
namespace EPD_7in3e {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_7in3e.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 800;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 480;

enum RefreshMode { Display = 0, EPD_7IN3E_Show7Block = 1, Display2 = 2 };

class EPD_7in3e_DrawTarget : public _6Color4BitEPD {
  public:
    std::string GetDeviceName() const override { return "7.3inch e-Paper (F)"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }
    
    // The following functions were not created:

    //  ! EPD_7IN3E_Clear(UBYTE color) was skipped because I'm not sure what arguments to pass in!

    /// @brief Initialize the display
    void Init() {
        controller::EPD_7IN3E_Init();
    }

    /// @brief Initialize the display
    void Init_Fast() {
        controller::EPD_7IN3E_Init_Fast();
    }

    /// @brief Put the display to sleep
    void Sleep() {
        controller::EPD_7IN3E_Sleep();
    }

    /// @brief Display pixels in buffers to display
    void Display() {
        controller::EPD_7IN3E_Show();
    }

    /// @brief Display pixels in buffers to display
    void EPD_7IN3E_Show7Block() {
        controller::EPD_7IN3E_Show7Block();
    }

    /// @brief Display pixels in buffers to display
    void Display2() {
        controller::EPD_7IN3E_Display(packedBits);
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

        case RefreshMode::EPD_7IN3E_Show7Block:
        EPD_7IN3E_Show7Block();
        break;

        case RefreshMode::Display2:
        Display2();
        break;


        default:
            throw UnsupportedRefreshMode(mode, GetDeviceName());
        }
        
    }

    EPD_7in3e_DrawTarget(bool initializeSPI = true) : _6Color4BitEPD(GetWidth(), GetHeight(), initializeSPI) {}
    ~EPD_7in3e_DrawTarget() {}
};

} // namespace EPD_7in3e

} // namespace devices

} // namespace epaperapi