/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 2.7inch V2 e-paper
 * Shortname: EPD_2in7_V2
 * Generated On: 26 April 2025 @ 5:41 PM
 * Supported Color Channels: black
 * Type: Black1BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "2.7inch V2 e-paper",
 *   "ScreenWidth": 176,
 *   "ScreenHeight": 264,
 *   "SupportedColorChannels": [
 *     "black"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_2IN7_V2_Init(void)",
 *       "EPD_2IN7_V2_Init_Fast(void)",
 *       "EPD_2IN7_V2_Init_4GRAY(void)"
 *     ],
 *     "Clear": [
 *       "EPD_2IN7_V2_Clear(void)"
 *     ],
 *     "Display": [
 *       "EPD_2IN7_V2_Display(UBYTE *Image)"
 *     ],
 *     "Display_Base": [
 *       "EPD_2IN7_V2_Display_Base(UBYTE *Image)"
 *     ],
 *     "Display_Partial": [
 *       "EPD_2IN7_V2_Display_Partial(const UBYTE *Image, UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yende)"
 *     ],
 *     "Display_Fast": [
 *       "EPD_2IN7_V2_Display_Fast(UBYTE *Image)"
 *     ],
 *     "Display_Misc": [
 *       "EPD_2IN7_V2_Display_Base_color(UBYTE color)",
 *       "EPD_2IN7_V2_4GrayDisplay(UBYTE *Image)"
 *     ],
 *     "Sleep": [
 *       "EPD_2IN7_V2_Sleep(void)"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "The SupportedColorChannels is set to 'black' due to the presence of 4GRAY_INITIALIZE function suggesting
 * support for gray shades, which are interpreted under the 'black' channel according to the rules. The function
 * EPD_2IN7_V2_4GrayDisplay might suggest more complex color support, but under current guidelines, no additional colors
 * are added.",
 *   "PaintScale": 2,
 *   "PaintRotation": 90,
 *   "BitmapFunction": "GUI_ReadBmp"
 * }
 */
 
#pragma once

#include "../EPD_Common.h"

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief 2.7inch V2 e-paper
namespace EPD_2in7_V2 {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_2in7_V2.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 176;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 264;

enum RefreshMode { Display = 0, Base = 1, Fast = 2, Display2 = 3, Base_color = 4 };

class EPD_2in7_V2_DrawTarget : public Black1BitEPD {
  public:
    std::string GetDeviceName() const override { return "2.7inch V2 e-paper"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }
    
    // The following functions were not created:

    //  ! EPD_2IN7_V2_Display_Partial(const UBYTE *Image, UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yende) was skipped because I'm not sure what arguments to pass in!

    /// @brief Initialize the display
    void Init() {
        controller::EPD_2IN7_V2_Init();
    }

    /// @brief Initialize the display
    void Init_Fast() {
        controller::EPD_2IN7_V2_Init_Fast();
    }

    /// @brief Initialize the display
    void Init_4GRAY() {
        controller::EPD_2IN7_V2_Init_4GRAY();
    }

    /// @brief Clear the display
    void Clear() {
        controller::EPD_2IN7_V2_Clear();
    }

    /// @brief Put the display to sleep
    void Sleep() {
        controller::EPD_2IN7_V2_Sleep();
    }

    /// @brief Display pixels in buffers to display
    void Display() {
        controller::EPD_2IN7_V2_Display(packedBits);
    }

    /// @brief Display pixels in buffers to display
    void Display_Base() {
        controller::EPD_2IN7_V2_Display_Base(packedBits);
    }

    /// @brief Display pixels in buffers to display
    void Display_Fast() {
        controller::EPD_2IN7_V2_Display_Fast(packedBits);
    }

    /// @brief Display pixels in buffers to display
    void Display2() {
        controller::EPD_2IN7_V2_4GrayDisplay(packedBits);
    }

    /// @brief Display pixels in buffers to display
    void Display_Base_color() {
        controller::EPD_2IN7_V2_Display_Base_color(packedBits);
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

        case RefreshMode::Base:
        Display_Base();
        break;

        case RefreshMode::Fast:
        Display_Fast();
        break;

        case RefreshMode::Display2:
        Display2();
        break;

        case RefreshMode::Base_color:
        Display_Base_color();
        break;


        default:
            throw UnsupportedRefreshMode(mode, GetDeviceName());
        }
        
    }

    EPD_2in7_V2_DrawTarget(bool initializeSPI = true) : Black1BitEPD(GetWidth(), GetHeight(), initializeSPI) {}
    ~EPD_2in7_V2_DrawTarget() {}
};

} // namespace EPD_2in7_V2

} // namespace devices

} // namespace epaperapi