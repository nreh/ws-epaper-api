/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 2.13inch e-paper V4
 * Shortname: EPD_2in13_V4
 * Generated On: 26 April 2025 @ 5:41 PM
 * Supported Color Channels: black
 * Type: Black1BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "2.13inch e-paper V4",
 *   "ScreenWidth": 122,
 *   "ScreenHeight": 250,
 *   "SupportedColorChannels": [
 *     "black"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_2in13_V4_Init(void)",
 *       "EPD_2in13_V4_Init_Fast(void)",
 *       "EPD_2in13_V4_Init_GUI(void)"
 *     ],
 *     "Clear": [
 *       "EPD_2in13_V4_Clear(void)",
 *       "EPD_2in13_V4_Clear_Black(void)"
 *     ],
 *     "Display": [
 *       "EPD_2in13_V4_Display(UBYTE *Image)"
 *     ],
 *     "Display_Base": [
 *       "EPD_2in13_V4_Display_Base(UBYTE *Image)"
 *     ],
 *     "Display_Partial": [
 *       "EPD_2in13_V4_Display_Partial(UBYTE *Image)"
 *     ],
 *     "Display_Fast": [
 *       "EPD_2in13_V4_Display_Fast(UBYTE *Image)"
 *     ],
 *     "Display_Misc": [],
 *     "Sleep": [
 *       "EPD_2in13_V4_Sleep(void)"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "Only black is supported explicitly as all functions and clears reference 'black'. The function
 * EPD_2in13_V4_Init_GUI doesn't indicate a specific display capability but is included for comprehensive
 * initialization.",
 *   "PaintRotation": 90,
 *   "BitmapFunction": "GUI_ReadBmp"
 * }
 */
 
#pragma once

#include "../EPD_Common.h"

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief 2.13inch e-paper V4
namespace EPD_2in13_V4 {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_2in13_V4.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 122;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 250;

enum RefreshMode { Display = 0, Partial = 1, Base = 2, Fast = 3 };

class EPD_2in13_V4_DrawTarget : public Black1BitEPD {
  public:
    std::string GetDeviceName() const override { return "2.13inch e-paper V4"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }
    
    /// @brief Initialize the display
    void Init() {
        controller::EPD_2in13_V4_Init();
    }

    /// @brief Initialize the display
    void Init_GUI() {
        controller::EPD_2in13_V4_Init_GUI();
    }

    /// @brief Initialize the display
    void Init_Fast() {
        controller::EPD_2in13_V4_Init_Fast();
    }

    /// @brief Clear the display
    void Clear() {
        controller::EPD_2in13_V4_Clear();
    }

    /// @brief Clear the display
    void Clear_Black() {
        controller::EPD_2in13_V4_Clear_Black();
    }

    /// @brief Put the display to sleep
    void Sleep() {
        controller::EPD_2in13_V4_Sleep();
    }

    /// @brief Display pixels in buffers to display
    void Display() {
        controller::EPD_2in13_V4_Display(packedBits);
    }

    /// @brief Display pixels in buffers to display
    void Display_Base() {
        controller::EPD_2in13_V4_Display_Base(packedBits);
    }

    /// @brief Display pixels in buffers to display
    void Display_Fast() {
        controller::EPD_2in13_V4_Display_Fast(packedBits);
    }

    /// @brief Display pixels in buffers to display
    void Display_Partial() {
        controller::EPD_2in13_V4_Display_Partial(packedBits);
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


        default:
            throw UnsupportedRefreshMode(mode, GetDeviceName());
        }
        
    }

    EPD_2in13_V4_DrawTarget(bool initializeSPI = true) : Black1BitEPD(GetWidth(), GetHeight(), initializeSPI) {}
    ~EPD_2in13_V4_DrawTarget() {}
};

} // namespace EPD_2in13_V4

} // namespace devices

} // namespace epaperapi