/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 2.7inch e-paper
 * Shortname: EPD_2in7
 * Generated On: 26 April 2025 @ 5:41 PM
 * Supported Color Channels: black
 * Type: Black2BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "2.7inch e-paper",
 *   "ScreenWidth": 176,
 *   "ScreenHeight": 264,
 *   "SupportedColorChannels": [
 *     "black"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_2IN7_Init(void)",
 *       "EPD_2IN7_Init_4Gray(void)"
 *     ],
 *     "Clear": [
 *       "EPD_2IN7_Clear(void)"
 *     ],
 *     "Display": [
 *       "EPD_2IN7_Display(const UBYTE *Image)",
 *       "EPD_2IN7_4GrayDisplay(const UBYTE *Image)"
 *     ],
 *     "Display_Base": [],
 *     "Display_Partial": [],
 *     "Display_Fast": [],
 *     "Display_Misc": [],
 *     "Sleep": [
 *       "EPD_2IN7_Sleep(void)"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "The functions indicate support for '4 grayscale display', with 'EPD_2IN7_4GrayDisplay' specifically
 * handling grayscale. However, 'gray' should be ignored and falls under 'black' in SupportedColorChannels, adhering to
 * the specifications given to only list 'black'.",
 *   "PaintScale": 4,
 *   "PaintRotation": 270,
 *   "BitmapFunction": "GUI_ReadBmp"
 * }
 */

#pragma once

#include "../EPD_Common.h"

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief 2.7inch e-paper
namespace EPD_2in7 {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_2in7.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 176;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 264;

enum RefreshMode { Display = 0, EPD_2IN7_4GrayDisplay = 1 };

class EPD_2in7_DrawTarget : public Black2BitEPD {
  public:
    std::string GetDeviceName() const override { return "2.7inch e-paper"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }

    /// @brief Initialize the display
    void Init() { controller::EPD_2IN7_Init(); }

    /// @brief Initialize the display
    void Init_4Gray() { controller::EPD_2IN7_Init_4Gray(); }

    /// @brief Clear the display
    void Clear() { controller::EPD_2IN7_Clear(); }

    /// @brief Put the display to sleep
    void Sleep() { controller::EPD_2IN7_Sleep(); }

    /// @brief Display pixels in 1 bit buffer to display
    void Display() { controller::EPD_2IN7_Display(packedBits_1bit); }

    /// @brief Display pixels in 2 bit buffer to display (4 shades of gray)
    void EPD_2IN7_4GrayDisplay() { controller::EPD_2IN7_4GrayDisplay(packedBits_2bit); }

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

        case RefreshMode::EPD_2IN7_4GrayDisplay:
            EPD_2IN7_4GrayDisplay();
            break;

        default:
            throw UnsupportedRefreshMode(mode, GetDeviceName());
        }
    }

    EPD_2in7_DrawTarget(bool initialize = true) : Black2BitEPD(GetWidth(), GetHeight(), initialize) {
        if (initialize)
            Init();
    }
    ~EPD_2in7_DrawTarget() {}
};

} // namespace EPD_2in7

} // namespace devices

} // namespace epaperapi