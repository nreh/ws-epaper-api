/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 7.5inch e-paper V2
 * Shortname: EPD_7in5_V2
 * Generated On: 26 April 2025 @ 5:41 PM
 * Supported Color Channels: black
 * Type: Black1BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "7.5inch e-paper V2",
 *   "ScreenWidth": 800,
 *   "ScreenHeight": 480,
 *   "SupportedColorChannels": [
 *     "black"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_7IN5_V2_Init()",
 *       "EPD_7IN5_V2_Init_Fast()",
 *       "EPD_7IN5_V2_Init_Part()"
 *     ],
 *     "Clear": [
 *       "EPD_7IN5_V2_Clear()",
 *       "EPD_7IN5_V2_ClearBlack()"
 *     ],
 *     "Display": [
 *       "EPD_7IN5_V2_Display(UBYTE *blackimage)"
 *     ],
 *     "Display_Base": [],
 *     "Display_Partial": [
 *       "EPD_7IN5_V2_Display_Part(UBYTE *blackimage, UDOUBLE x_start, UDOUBLE y_start, UDOUBLE x_end, UDOUBLE y_end)"
 *     ],
 *     "Display_Fast": [],
 *     "Display_Misc": [],
 *     "Sleep": [
 *       "EPD_7IN5_V2_Sleep()"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "The display only uses a single channel, presumed to be 'black', as indicated by the argument in
 * EPD_7IN5_V2_Display(), EPD_7IN5_V2_Display_Part(), and related functions. No mention of additional color channels
 * like red, blue, etc., was found.",
 *   "PaintRotation": 0,
 *   "BitmapFunction": "GUI_ReadBmp"
 * }
 */

#pragma once

#include "../EPD_Common.h"

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief 7.5inch e-paper V2
namespace EPD_7in5_V2 {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_7in5_V2.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 800;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 480;

enum RefreshMode { Display = 0 };

class EPD_7in5_V2_DrawTarget : public Black1BitEPD {
  public:
    std::string GetDeviceName() const override { return "7.5inch e-paper V2"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }

    // The following functions were not created:

    //  ! EPD_7IN5_V2_Display_Part(UBYTE *blackimage, UDOUBLE x_start, UDOUBLE y_start, UDOUBLE x_end, UDOUBLE y_end) was
    //  skipped because I'm not sure what arguments to pass in!

    /// @brief Initialize the display
    void Init() { controller::EPD_7IN5_V2_Init(); }

    /// @brief Initialize the display
    void Init_Fast() { controller::EPD_7IN5_V2_Init_Fast(); }

    /// @brief Initialize the display
    void Init_Part() { controller::EPD_7IN5_V2_Init_Part(); }

    /// @brief Clear the display
    void Clear() { controller::EPD_7IN5_V2_Clear(); }

    /// @brief Clear the display
    void ClearBlack() { controller::EPD_7IN5_V2_ClearBlack(); }

    /// @brief Put the display to sleep
    void Sleep() { controller::EPD_7IN5_V2_Sleep(); }

    /// @brief Display pixels in buffers to display
    void Display() { controller::EPD_7IN5_V2_Display(packedBits); }

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

    EPD_7in5_V2_DrawTarget(bool initialize = true) : Black1BitEPD(GetWidth(), GetHeight(), initialize) {
        if (initialize)
            Init();
    }
    ~EPD_7in5_V2_DrawTarget() {}
};

} // namespace EPD_7in5_V2

} // namespace devices

} // namespace epaperapi