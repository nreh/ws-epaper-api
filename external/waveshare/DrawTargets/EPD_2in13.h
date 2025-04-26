/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 2.13inch e-paper V3
 * Shortname: EPD_2in13
 * Generated On: 26 April 2025 @ 5:41 PM
 * Supported Color Channels: black
 * Type: Black1BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "2.13inch e-paper V3",
 *   "ScreenWidth": 122,
 *   "ScreenHeight": 250,
 *   "SupportedColorChannels": [
 *     "black"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_2IN13_Init(UBYTE Mode)"
 *     ],
 *     "Clear": [
 *       "EPD_2IN13_Clear(void)"
 *     ],
 *     "Display": [
 *       "EPD_2IN13_Display(UBYTE *Image)"
 *     ],
 *     "Display_Base": [],
 *     "Display_Partial": [],
 *     "Display_Fast": [],
 *     "Display_Misc": [],
 *     "Sleep": [
 *       "EPD_2IN13_Sleep(void)"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "Only one color channel (UBYTE *Image) is used in the EPD_2IN13_Display function, so 'black' is assumed.
 * No other color indications are present. Functions like EPD_2IN13_Init and EPD_2IN13_Clear have clear categorization.
 * The function EPD_2IN13_Display is assumed to represent basic display capabilities since there's no other function for
 * displaying methods.",
 *   "PaintRotation": 270,
 *   "BitmapFunction": "GUI_ReadBmp"
 * }
 */
 
#pragma once

#include "../EPD_Common.h"

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief 2.13inch e-paper V3
namespace EPD_2in13 {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_2in13.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 122;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 250;

enum RefreshMode { Display = 0 };

class EPD_2in13_DrawTarget : public Black1BitEPD {
  public:
    std::string GetDeviceName() const override { return "2.13inch e-paper V3"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }
    
    // The following functions were not created:

    //  ! EPD_2IN13_Init(UBYTE Mode) was skipped because I'm not sure what arguments to pass in!

    /// @brief Clear the display
    void Clear() {
        controller::EPD_2IN13_Clear();
    }

    /// @brief Put the display to sleep
    void Sleep() {
        controller::EPD_2IN13_Sleep();
    }

    /// @brief Display pixels in buffers to display
    void Display() {
        controller::EPD_2IN13_Display(packedBits);
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

    EPD_2in13_DrawTarget(bool initializeSPI = true) : Black1BitEPD(GetWidth(), GetHeight(), initializeSPI) {}
    ~EPD_2in13_DrawTarget() {}
};

} // namespace EPD_2in13

} // namespace devices

} // namespace epaperapi