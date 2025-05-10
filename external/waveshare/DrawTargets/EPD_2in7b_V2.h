/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 2.7inch e-paper V2
 * Shortname: EPD_2in7b_V2
 * Generated On: 26 April 2025 @ 5:41 PM
 * Supported Color Channels: black,red
 * Type: RedBlack1BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "2.7inch e-paper V2",
 *   "ScreenWidth": 176,
 *   "ScreenHeight": 264,
 *   "SupportedColorChannels": [
 *     "black",
 *     "red"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_2IN7B_V2_Init()"
 *     ],
 *     "Clear": [
 *       "EPD_2IN7B_V2_Clear()"
 *     ],
 *     "Display": [
 *       "EPD_2IN7B_V2_Display(UBYTE *Imageblack, UBYTE *Imagered)"
 *     ],
 *     "Display_Base": [],
 *     "Display_Partial": [],
 *     "Display_Fast": [],
 *     "Display_Misc": [],
 *     "Sleep": [
 *       "EPD_2IN7B_V2_Sleep()"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "The EPD_2IN7B_V2_Display function indicates a dual-color display using black and red channels. Function
 * categorization was straightforward given the typical e-paper operations.",
 *   "PaintRotation": 270,
 *   "BitmapFunction": "GUI_ReadBmp"
 * }
 */

#pragma once

#include "../EPD_Common.h"

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief 2.7inch e-paper V2
namespace EPD_2in7b_V2 {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_2in7b_V2.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 176;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 264;

enum RefreshMode { Display = 0 };

class EPD_2in7b_V2_DrawTarget : public RedBlack1BitEPD {
  public:
    std::string GetDeviceName() const override { return "2.7inch e-paper V2"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }

    /// @brief Initialize the display
    void Init() { controller::EPD_2IN7B_V2_Init(); }

    /// @brief Clear the display
    void Clear() { controller::EPD_2IN7B_V2_Clear(); }

    /// @brief Put the display to sleep
    void Sleep() { controller::EPD_2IN7B_V2_Sleep(); }

    /// @brief Display pixels in buffers to display
    void Display() { controller::EPD_2IN7B_V2_Display(packedBitsBlack, packedBitsRed); }

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

    EPD_2in7b_V2_DrawTarget(bool initialize = true) : RedBlack1BitEPD(GetWidth(), GetHeight(), initialize) {
        if (initialize)
            Init();
    }
    ~EPD_2in7b_V2_DrawTarget() {}
};

} // namespace EPD_2in7b_V2

} // namespace devices

} // namespace epaperapi