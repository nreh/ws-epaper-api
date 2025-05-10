/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: EPD 7.5 inch HD
 * Shortname: EPD_7in5_HD
 * Generated On: 26 April 2025 @ 5:41 PM
 * Supported Color Channels: black
 * Type: Black1BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "EPD 7.5 inch HD",
 *   "ScreenWidth": 880,
 *   "ScreenHeight": 528,
 *   "SupportedColorChannels": [
 *     "black"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_7IN5_HD_Init(void)"
 *     ],
 *     "Clear": [
 *       "EPD_7IN5_HD_Clear(void)",
 *       "EPD_7IN5_HD_ClearBlack(void)"
 *     ],
 *     "Display": [
 *       "EPD_7IN5_HD_Display(const UBYTE *blackimage)"
 *     ],
 *     "Display_Base": [],
 *     "Display_Partial": [],
 *     "Display_Fast": [],
 *     "Display_Misc": [],
 *     "Sleep": [
 *       "EPD_7IN5_HD_Sleep(void)"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "Only `black` color channel is explicitly mentioned since the display function `EPD_7IN5_HD_Display` only
 * uses a `blackimage`. The `ClearBlack` function implies a focus on `black` as well. 'gray' or 'white' colors are not
 * mentioned and hence are not part of SupportedColorChannels.",
 *   "PaintRotation": 0,
 *   "BitmapFunction": "GUI_ReadBmp"
 * }
 */

#pragma once

#include "../EPD_Common.h"

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief EPD 7.5 inch HD
namespace EPD_7in5_HD {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_7in5_HD.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 880;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 528;

enum RefreshMode { Display = 0 };

class EPD_7in5_HD_DrawTarget : public Black1BitEPD {
  public:
    std::string GetDeviceName() const override { return "EPD 7.5 inch HD"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }

    /// @brief Initialize the display
    void Init() { controller::EPD_7IN5_HD_Init(); }

    /// @brief Clear the display
    void Clear() { controller::EPD_7IN5_HD_Clear(); }

    /// @brief Clear the display
    void ClearBlack() { controller::EPD_7IN5_HD_ClearBlack(); }

    /// @brief Put the display to sleep
    void Sleep() { controller::EPD_7IN5_HD_Sleep(); }

    /// @brief Display pixels in buffers to display
    void Display() { controller::EPD_7IN5_HD_Display(packedBits); }

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

    EPD_7in5_HD_DrawTarget(bool initialize = true) : Black1BitEPD(GetWidth(), GetHeight(), initialize) {
        if (initialize)
            Init();
    }
    ~EPD_7in5_HD_DrawTarget() {}
};

} // namespace EPD_7in5_HD

} // namespace devices

} // namespace epaperapi