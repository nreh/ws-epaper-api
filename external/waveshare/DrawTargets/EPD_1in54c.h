/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 1.54inch e-paper c
 * Shortname: EPD_1in54c
 * Generated On: 26 April 2025 @ 5:41 PM
 * Supported Color Channels: black,red
 * Type: RedBlack1BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "1.54inch e-paper c",
 *   "ScreenWidth": 152,
 *   "ScreenHeight": 152,
 *   "SupportedColorChannels": [
 *     "black",
 *     "red"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_1IN54C_Init(void)"
 *     ],
 *     "Clear": [
 *       "EPD_1IN54C_Clear(void)"
 *     ],
 *     "Display": [
 *       "EPD_1IN54C_Display(const UBYTE *blackimage, const UBYTE *redimage)"
 *     ],
 *     "Display_Base": [],
 *     "Display_Partial": [],
 *     "Display_Fast": [],
 *     "Display_Misc": [],
 *     "Sleep": [
 *       "EPD_1IN54C_Sleep(void)"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "The display supports 'black' and 'red', as indicated by the dual image channel parameters in the
 * EPD_1IN54C_Display function. This is a full-color capability with those specific colors.",
 *   "PaintRotation": 270,
 *   "BitmapFunction": "GUI_ReadBmp"
 * }
 */

#pragma once

#include "../EPD_Common.h"

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief 1.54inch e-paper c
namespace EPD_1in54c {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_1in54c.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 152;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 152;

enum RefreshMode { Display = 0 };

class EPD_1in54c_DrawTarget : public RedBlack1BitEPD {
  public:
    std::string GetDeviceName() const override { return "1.54inch e-paper c"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }

    /// @brief Initialize the display
    void Init() { controller::EPD_1IN54C_Init(); }

    /// @brief Clear the display
    void Clear() { controller::EPD_1IN54C_Clear(); }

    /// @brief Put the display to sleep
    void Sleep() { controller::EPD_1IN54C_Sleep(); }

    /// @brief Display pixels in buffers to display
    void Display() { controller::EPD_1IN54C_Display(packedBitsBlack, packedBitsRed); }

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

    EPD_1in54c_DrawTarget(bool initializeSPI = true) : RedBlack1BitEPD(GetWidth(), GetHeight(), initializeSPI) {}
    ~EPD_1in54c_DrawTarget() {}
};

} // namespace EPD_1in54c

} // namespace devices

} // namespace epaperapi