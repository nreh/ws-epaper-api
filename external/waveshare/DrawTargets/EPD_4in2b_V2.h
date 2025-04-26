/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 4.2inch e-paper b&c V1.0
 * Shortname: EPD_4in2b_V2
 * Generated On: 26 April 2025 @ 5:41 PM
 * Supported Color Channels: black,red
 * Type: RedBlack1BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "4.2inch e-paper b&c V1.0",
 *   "ScreenWidth": 400,
 *   "ScreenHeight": 300,
 *   "SupportedColorChannels": [
 *     "black",
 *     "red"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_4IN2B_V2_Init(void)"
 *     ],
 *     "Clear": [
 *       "EPD_4IN2B_V2_Clear(void)"
 *     ],
 *     "Display": [
 *       "EPD_4IN2B_V2_Display(const UBYTE *blackimage, const UBYTE *ryimage)"
 *     ],
 *     "Display_Base": [],
 *     "Display_Partial": [],
 *     "Display_Fast": [],
 *     "Display_Misc": [],
 *     "Sleep": [
 *       "EPD_4IN2B_V2_Sleep(void)"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "The function EPD_4IN2B_V2_Display uses two images, assumed to relate to 'black' and 'red' channels. No
 * additional colors or functionality descriptions are apparent from the function names or comments.",
 *   "PaintRotation": 180,
 *   "BitmapFunction": "GUI_ReadBmp"
 * }
 */

#pragma once

#include "../EPD_Common.h"

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief 4.2inch e-paper b&c V1.0
namespace EPD_4in2b_V2 {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_4in2b_V2.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 400;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 300;

enum RefreshMode { Display = 0 };

class EPD_4in2b_V2_DrawTarget : public RedBlack1BitEPD {
  public:
    std::string GetDeviceName() const override { return "4.2inch e-paper b&c V1.0"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }

    /// @brief Initialize the display
    void Init() { controller::EPD_4IN2B_V2_Init(); }

    /// @brief Clear the display
    void Clear() { controller::EPD_4IN2B_V2_Clear(); }

    /// @brief Put the display to sleep
    void Sleep() { controller::EPD_4IN2B_V2_Sleep(); }

    /// @brief Display pixels in buffers to display
    void Display() { controller::EPD_4IN2B_V2_Display(packedBitsBlack, packedBitsRed); }

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

    EPD_4in2b_V2_DrawTarget(bool initializeSPI = true) : RedBlack1BitEPD(GetWidth(), GetHeight(), initializeSPI) {}
    ~EPD_4in2b_V2_DrawTarget() {}
};

} // namespace EPD_4in2b_V2

} // namespace devices

} // namespace epaperapi