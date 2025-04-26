/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 1.02inch e-paper
 * Shortname: EPD_1in02d
 * Generated On: 26 April 2025 @ 5:41 PM
 * Supported Color Channels: black
 * Type: Black1BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "1.02inch e-paper",
 *   "ScreenWidth": 80,
 *   "ScreenHeight": 128,
 *   "SupportedColorChannels": [
 *     "black"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_1IN02_Init()",
 *       "EPD_1IN02_Part_Init()"
 *     ],
 *     "Clear": [
 *       "EPD_1IN02_Clear()"
 *     ],
 *     "Display": [
 *       "EPD_1IN02_Display(UBYTE *Image)"
 *     ],
 *     "Display_Base": [],
 *     "Display_Partial": [
 *       "EPD_1IN02_DisplayPartial(UBYTE *Image1, UBYTE *Image2)"
 *     ],
 *     "Display_Fast": [],
 *     "Display_Misc": [],
 *     "Sleep": [
 *       "EPD_1IN02_Sleep()"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "The display supports only the black color channel as no other colors were specified.
 * EPD_1IN02_DisplayPartial was categorized under Display_Partial due to its name and function signature implying
 * partial image updates. Two initialization functions are present, one of which implies partial updates, but they both
 * are listed under Initialize. The display functions were straightforwardly categorized based on their names.",
 *   "PaintRotation": 270,
 *   "BitmapFunction": "GUI_ReadBmp"
 * }
 */
 
#pragma once

#include "../EPD_Common.h"

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief 1.02inch e-paper
namespace EPD_1in02d {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_1in02d.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 80;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 128;

enum RefreshMode { Display = 0 };

class EPD_1in02d_DrawTarget : public Black1BitEPD {
  public:
    std::string GetDeviceName() const override { return "1.02inch e-paper"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }
    
    // The following functions were not created:

    //  ! EPD_1IN02_DisplayPartial(UBYTE *Image1, UBYTE *Image2) was skipped because I'm not sure what arguments to pass in!

    /// @brief Initialize the display
    void Init() {
        controller::EPD_1IN02_Init();
    }

    /// @brief Initialize the display
    void Init2() {
        controller::EPD_1IN02_Part_Init();
    }

    /// @brief Clear the display
    void Clear() {
        controller::EPD_1IN02_Clear();
    }

    /// @brief Put the display to sleep
    void Sleep() {
        controller::EPD_1IN02_Sleep();
    }

    /// @brief Display pixels in buffers to display
    void Display() {
        controller::EPD_1IN02_Display(packedBits);
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

    EPD_1in02d_DrawTarget(bool initializeSPI = true) : Black1BitEPD(GetWidth(), GetHeight(), initializeSPI) {}
    ~EPD_1in02d_DrawTarget() {}
};

} // namespace EPD_1in02d

} // namespace devices

} // namespace epaperapi