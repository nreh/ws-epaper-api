/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 2.9inch e-paper
 * Shortname: EPD_2in9
 * Generated On: 26 April 2025 @ 5:41 PM
 * Supported Color Channels: black
 * Type: Black1BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "2.9inch e-paper",
 *   "ScreenWidth": 128,
 *   "ScreenHeight": 296,
 *   "SupportedColorChannels": [
 *     "black"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_2IN9_Init(UBYTE Mode)"
 *     ],
 *     "Clear": [
 *       "EPD_2IN9_Clear(void)"
 *     ],
 *     "Display": [
 *       "EPD_2IN9_Display(UBYTE *Image)"
 *     ],
 *     "Display_Base": [],
 *     "Display_Partial": [],
 *     "Display_Fast": [],
 *     "Display_Misc": [],
 *     "Sleep": [
 *       "EPD_2IN9_Sleep(void)"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "The SupportedColorChannels is set to 'black' as there are no indications of any color support beyond
 * black and white. No functions suggest the support of additional color channels.",
 *   "PaintRotation": 270,
 *   "BitmapFunction": "GUI_ReadBmp"
 * }
 */

#pragma once

#include "../EPD_Common.h"

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief 2.9inch e-paper
namespace EPD_2in9 {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_2in9.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 128;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 296;

enum RefreshMode { Display = 0 };

class EPD_2in9_DrawTarget : public Black1BitEPD {
  public:
    std::string GetDeviceName() const override { return "2.9inch e-paper"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }

    // The following functions were not created:

    //  ! EPD_2IN9_Init(UBYTE Mode) was skipped because I'm not sure what arguments to pass in!

    /// @brief Clear the display
    void Clear() { controller::EPD_2IN9_Clear(); }

    /// @brief Put the display to sleep
    void Sleep() { controller::EPD_2IN9_Sleep(); }

    /// @brief Display pixels in buffers to display
    void Display() { controller::EPD_2IN9_Display(packedBits); }

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

    EPD_2in9_DrawTarget(bool initializeSPI = true) : Black1BitEPD(GetWidth(), GetHeight(), initializeSPI) {}
    ~EPD_2in9_DrawTarget() {}
};

} // namespace EPD_2in9

} // namespace devices

} // namespace epaperapi