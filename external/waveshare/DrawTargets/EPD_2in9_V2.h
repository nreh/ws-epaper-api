/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 2.9inch e-paper V2
 * Shortname: EPD_2in9_V2
 * Generated On: 27 January 2025 @ 2:59 AM
 * Supported Color Channels: black
 * Type: Black2BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "2.9inch e-paper V2",
 *   "ScreenWidth": 128,
 *   "ScreenHeight": 296,
 *   "SupportedColorChannels": [
 *     "black"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_2IN9_V2_Init(void)",
 *       "EPD_2IN9_V2_Init_Fast(void)",
 *       "EPD_2IN9_V2_Gray4_Init(void)"
 *     ],
 *     "Clear": [
 *       "EPD_2IN9_V2_Clear(void)"
 *     ],
 *     "Display": [
 *       "EPD_2IN9_V2_Display(UBYTE *Image)"
 *     ],
 *     "Display_Base": [
 *       "EPD_2IN9_V2_Display_Base(UBYTE *Image)"
 *     ],
 *     "Display_Partial": [
 *       "EPD_2IN9_V2_Display_Partial(UBYTE *Image)"
 *     ],
 *     "Display_Fast": [
 *       "EPD_2IN9_V2_Display_Fast(UBYTE *Image)"
 *     ],
 *     "Display_Misc": [
 *       "EPD_2IN9_V2_4GrayDisplay(UBYTE *Image)"
 *     ],
 *     "Sleep": [
 *       "EPD_2IN9_V2_Sleep(void)"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "The display supports only black and shades of gray, hence only 'black' is listed under color channels.
 * The function EPD_2IN9_V2_Gray4_Init indicates grayscale support but is covered under 'black'.
 * EPD_2IN9_V2_4GrayDisplay suggests 4-gray level support, also categorized under 'Display_Misc'.",
 *   "PaintScale": 4,
 *   "PaintRotation": 90,
 *   "BitmapFunction": "GUI_ReadBmp"
 * }
 */
 
#pragma once

#include "../EPD_Common.h"

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief 2.9inch e-paper V2
namespace EPD_2in9_V2 {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_2in9_V2.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 128;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 296;

enum RefreshMode { Display = 0, Partial = 1, Base = 2, Fast = 3, EPD_2IN9_V2_4GrayDisplay = 4 };

class EPD_2in9_V2_DrawTarget : public Black2BitEPD {
  public:
    std::string GetDeviceName() const override { return "2.9inch e-paper V2"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }
    
    /// @brief Initialize the display
    void Init() {
        controller::EPD_2IN9_V2_Init();
    }

    /// @brief Initialize the display
    void Init_Fast() {
        controller::EPD_2IN9_V2_Init_Fast();
    }

    /// @brief Initialize the display
    void Init() {
        controller::EPD_2IN9_V2_Gray4_Init();
    }

    /// @brief Clear the display
    void Clear() {
        controller::EPD_2IN9_V2_Clear();
    }

    /// @brief Put the display to sleep
    void Sleep() {
        controller::EPD_2IN9_V2_Sleep();
    }

    /// @brief Display pixels in 1 bit buffer to display
    void Display() {
        controller::EPD_2IN9_V2_Display(packedBits_1bit);
    }

    /// @brief Display pixels in 1 bit buffer to display
    void Display_Base() {
        controller::EPD_2IN9_V2_Display_Base(packedBits_1bit);
    }

    /// @brief Display pixels in 1 bit buffer to display
    void Display_Fast() {
        controller::EPD_2IN9_V2_Display_Fast(packedBits_1bit);
    }

    /// @brief Display pixels in 1 bit buffer to display
    void Display_Partial() {
        controller::EPD_2IN9_V2_Display_Partial(packedBits_1bit);
    }

    /// @brief Display pixels in 2 bit buffer to display (4 shades of gray)
    void EPD_2IN9_V2_4GrayDisplay() {
        controller::EPD_2IN9_V2_4GrayDisplay(packedBits_2bit);
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

        case RefreshMode::Partial:
        Display_Partial();
        break;

        case RefreshMode::EPD_2IN9_V2_4GrayDisplay:
        EPD_2IN9_V2_4GrayDisplay();
        break;


        default:
            throw UnsupportedRefreshMode(mode, GetDeviceName());
        }
        
    }

    EPD_2in9_V2_DrawTarget() : Black2BitEPD(GetWidth(), GetHeight()) {}
    ~EPD_2in9_V2_DrawTarget() {}
};

} // namespace EPD_2in9_V2

} // namespace devices

} // namespace epaperapi