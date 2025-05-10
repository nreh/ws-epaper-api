/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 2.13inch e-paper b V3
 * Shortname: EPD_2in13b_V3
 * Generated On: 26 April 2025 @ 5:41 PM
 * Supported Color Channels: black,red
 * Type: RedBlack1BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "2.13inch e-paper b V3",
 *   "ScreenWidth": 104,
 *   "ScreenHeight": 212,
 *   "SupportedColorChannels": [
 *     "black",
 *     "red"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_2IN13B_V3_Init()"
 *     ],
 *     "Clear": [
 *       "EPD_2IN13B_V3_Clear()"
 *     ],
 *     "Display": [
 *       "EPD_2IN13B_V3_Display(const UBYTE *blackimage, const UBYTE *ryimage)"
 *     ],
 *     "Display_Base": [],
 *     "Display_Partial": [],
 *     "Display_Fast": [],
 *     "Display_Misc": [],
 *     "Sleep": [
 *       "EPD_2IN13B_V3_Sleep()"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "The display supports two color channels: black and red, as indicated by the parameters in the
 * EPD_2IN13B_V3_Display() function. 'ryimage' suggests the second channel is 'red/yellow' but for simplicity, it's
 * assumed to mean red in the SupportedColorChannels list.",
 *   "PaintRotation": 270,
 *   "BitmapFunction": "GUI_ReadBmp"
 * }
 */

#pragma once

#include "../EPD_Common.h"

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief 2.13inch e-paper b V3
namespace EPD_2in13b_V3 {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_2in13b_V3.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 104;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 212;

enum RefreshMode { Display = 0 };

class EPD_2in13b_V3_DrawTarget : public RedBlack1BitEPD {
  public:
    std::string GetDeviceName() const override { return "2.13inch e-paper b V3"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }

    /// @brief Initialize the display
    void Init() { controller::EPD_2IN13B_V3_Init(); }

    /// @brief Clear the display
    void Clear() { controller::EPD_2IN13B_V3_Clear(); }

    /// @brief Put the display to sleep
    void Sleep() { controller::EPD_2IN13B_V3_Sleep(); }

    /// @brief Display pixels in buffers to display
    void Display() { controller::EPD_2IN13B_V3_Display(packedBitsBlack, packedBitsRed); }

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

    EPD_2in13b_V3_DrawTarget(bool initialize = true) : RedBlack1BitEPD(GetWidth(), GetHeight(), initialize) {
        if (initialize)
            Init();
    }
    ~EPD_2in13b_V3_DrawTarget() {}
};

} // namespace EPD_2in13b_V3

} // namespace devices

} // namespace epaperapi