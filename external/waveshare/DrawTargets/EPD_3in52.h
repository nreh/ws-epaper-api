/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 3.52inch e-paper
 * Shortname: EPD_3in52
 * Generated On: 26 April 2025 @ 5:41 PM
 * Supported Color Channels: black
 * Type: Black1BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "3.52inch e-paper",
 *   "ScreenWidth": 240,
 *   "ScreenHeight": 360,
 *   "SupportedColorChannels": [
 *     "black"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_3IN52_Init()"
 *     ],
 *     "Clear": [
 *       "EPD_3IN52_Clear()"
 *     ],
 *     "Display": [
 *       "EPD_3IN52_display(UBYTE* picData)",
 *       "EPD_3IN52_display_NUM(UBYTE NUM)"
 *     ],
 *     "Display_Base": [],
 *     "Display_Partial": [],
 *     "Display_Fast": [],
 *     "Display_Misc": [
 *       "EPD_3IN52_refresh()",
 *       "EPD_3IN52_lut_GC()",
 *       "EPD_3IN52_lut_DU()"
 *     ],
 *     "Sleep": [
 *       "EPD_3IN52_sleep()"
 *     ],
 *     "Misc": [
 *       "EPD_3IN52_SendCommand(UBYTE Reg)",
 *       "EPD_3IN52_SendData(UBYTE Data)"
 *     ]
 *   },
 *   "Notes": "The header defines black as a basic color channel, and while multiple patterns of black and white are
 * defined (e.g., UP_BLACK_DOWN_WHITE), the primary color channel remains black without other colors. The functions have
 * been categorized based on their apparent functionality with a few falling under 'Display_Misc' due to their names
 * suggesting display-related operations but not fitting the main display pattern. Black and white patterns were
 * considered only as black, following predefined rules.",
 *   "PaintRotation": 270,
 *   "BitmapFunction": "GUI_ReadBmp"
 * }
 */

#pragma once

#include "../EPD_Common.h"

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief 3.52inch e-paper
namespace EPD_3in52 {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_3in52.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 240;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 360;

enum RefreshMode {
    Display = 0,
    EPD_3IN52_lut_DU = 1,
    EPD_3IN52_refresh = 2,
    EPD_3IN52_display_NUM = 3,
    EPD_3IN52_display = 4
};

class EPD_3in52_DrawTarget : public Black1BitEPD {
  public:
    std::string GetDeviceName() const override { return "3.52inch e-paper"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }

    /// @brief Initialize the display
    void Init() { controller::EPD_3IN52_Init(); }

    /// @brief Clear the display
    void Clear() { controller::EPD_3IN52_Clear(); }

    /// @brief Put the display to sleep
    void Sleep() { controller::EPD_3IN52_sleep(); }

    /// @brief Display pixels in buffers to display
    void Display() { controller::EPD_3IN52_lut_GC(); }

    /// @brief Display pixels in buffers to display
    void EPD_3IN52_lut_DU() { controller::EPD_3IN52_lut_DU(); }

    /// @brief Display pixels in buffers to display
    void EPD_3IN52_refresh() { controller::EPD_3IN52_refresh(); }

    /// @brief Display pixels in buffers to display
    void EPD_3IN52_display_NUM() { controller::EPD_3IN52_display_NUM(0xFF); }

    /// @brief Display pixels in buffers to display
    void EPD_3IN52_display() { controller::EPD_3IN52_display(packedBits); }

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

        case RefreshMode::EPD_3IN52_lut_DU:
            EPD_3IN52_lut_DU();
            break;

        case RefreshMode::EPD_3IN52_refresh:
            EPD_3IN52_refresh();
            break;

        case RefreshMode::EPD_3IN52_display_NUM:
            EPD_3IN52_display_NUM();
            break;

        case RefreshMode::EPD_3IN52_display:
            EPD_3IN52_display();
            break;

        default:
            throw UnsupportedRefreshMode(mode, GetDeviceName());
        }
    }

    EPD_3in52_DrawTarget(bool initialize = true) : Black1BitEPD(GetWidth(), GetHeight(), initialize) {
        if (initialize)
            Init();
    }
    ~EPD_3in52_DrawTarget() {}
};

} // namespace EPD_3in52

} // namespace devices

} // namespace epaperapi