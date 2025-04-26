/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 1.54inch e-paper
 * Shortname: EPD_1in54
 * Generated On: 26 April 2025 @ 5:41 PM
 * Supported Color Channels: black
 * Type: Black1BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "1.54inch e-paper",
 *   "ScreenWidth": 200,
 *   "ScreenHeight": 200,
 *   "SupportedColorChannels": [
 *     "black"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_1IN54_Init(UBYTE Mode)"
 *     ],
 *     "Clear": [
 *       "EPD_1IN54_Clear(void)"
 *     ],
 *     "Display": [
 *       "EPD_1IN54_Display(UBYTE *Image)"
 *     ],
 *     "Display_Base": [],
 *     "Display_Partial": [],
 *     "Display_Fast": [],
 *     "Display_Misc": [],
 *     "Sleep": [
 *       "EPD_1IN54_Sleep(void)"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "The display function EPD_1IN54_Display only takes one image parameter, which implies a single color
 * channel, identified as 'black'. It doesn't list gray or white, so the assumption holds that 'black' covers both.",
 *   "PaintRotation": 270,
 *   "BitmapFunction": "GUI_ReadBmp"
 * }
 */

#pragma once

#include "../EPD_Common.h"

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief 1.54inch e-paper
namespace EPD_1in54 {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_1in54.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 200;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 200;

enum RefreshMode { Display = 0 };

class EPD_1in54_DrawTarget : public Black1BitEPD {
  public:
    std::string GetDeviceName() const override { return "1.54inch e-paper"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }

    // The following functions were not created:

    //  ! EPD_1IN54_Init(UBYTE Mode) was skipped because I'm not sure what arguments to pass in!

    /// @brief Clear the display
    void Clear() { controller::EPD_1IN54_Clear(); }

    /// @brief Put the display to sleep
    void Sleep() { controller::EPD_1IN54_Sleep(); }

    /// @brief Display pixels in buffers to display
    void Display() { controller::EPD_1IN54_Display(packedBits); }

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

    EPD_1in54_DrawTarget(bool initializeSPI = true) : Black1BitEPD(GetWidth(), GetHeight(), initializeSPI) {}
    ~EPD_1in54_DrawTarget() {}
};

} // namespace EPD_1in54

} // namespace devices

} // namespace epaperapi