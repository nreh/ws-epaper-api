/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 5.79inch e-paper V1.0
 * Shortname: EPD_5in79b
 * Generated On: 26 April 2025 @ 5:41 PM
 * Supported Color Channels: black,red
 * Type: RedBlack1BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "5.79inch e-paper V1.0",
 *   "ScreenWidth": 792,
 *   "ScreenHeight": 272,
 *   "SupportedColorChannels": [
 *     "black",
 *     "red"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_5in79b_Init(void)"
 *     ],
 *     "Clear": [
 *       "EPD_5in79b_Clear(void)"
 *     ],
 *     "Display": [
 *       "EPD_5in79b_Display(const UBYTE *blackimage, const UBYTE *ryimage)"
 *     ],
 *     "Display_Base": [],
 *     "Display_Partial": [],
 *     "Display_Fast": [],
 *     "Display_Misc": [],
 *     "Sleep": [
 *       "EPD_5in79b_Sleep(void)"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "The EPD_5in79b_Display function uses two image pointers, which commonly refer to 'black' and 'red'
 * channels in similar headers. This assumption was made for the supported color channels. Function names suggest
 * straightforward categorization.",
 *   "PaintRotation": 0,
 *   "BitmapFunction": "GUI_ReadBmp"
 * }
 */

#pragma once

#include "../EPD_Common.h"

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief 5.79inch e-paper V1.0
namespace EPD_5in79b {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_5in79b.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 792;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 272;

enum RefreshMode { Display = 0 };

class EPD_5in79b_DrawTarget : public RedBlack1BitEPD {
  public:
    std::string GetDeviceName() const override { return "5.79inch e-paper V1.0"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }

    /// @brief Initialize the display
    void Init() { controller::EPD_5in79b_Init(); }

    /// @brief Clear the display
    void Clear() { controller::EPD_5in79b_Clear(); }

    /// @brief Put the display to sleep
    void Sleep() { controller::EPD_5in79b_Sleep(); }

    /// @brief Display pixels in buffers to display
    void Display() { controller::EPD_5in79b_Display(packedBitsBlack, packedBitsRed); }

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

    EPD_5in79b_DrawTarget(bool initializeSPI = true) : RedBlack1BitEPD(GetWidth(), GetHeight(), initializeSPI) {}
    ~EPD_5in79b_DrawTarget() {}
};

} // namespace EPD_5in79b

} // namespace devices

} // namespace epaperapi