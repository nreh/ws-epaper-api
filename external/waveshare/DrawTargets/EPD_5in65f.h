/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 5.65inch e-paper
 * Shortname: EPD_5in65f
 * Generated On: 26 April 2025 @ 5:41 PM
 * Supported Color Channels: black,green,blue,red,yellow,orange
 * Type: _7Color4BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "5.65inch e-paper",
 *   "ScreenWidth": 600,
 *   "ScreenHeight": 448,
 *   "SupportedColorChannels": [
 *     "black",
 *     "green",
 *     "blue",
 *     "red",
 *     "yellow",
 *     "orange"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_Init()",
 *       "EPD_5IN65F_Init()"
 *     ],
 *     "Clear": [
 *       "EPD_5IN65F_Clear(UBYTE color)"
 *     ],
 *     "Display": [
 *       "EPD_5IN65F_Display(const UBYTE *image)"
 *     ],
 *     "Display_Base": [],
 *     "Display_Partial": [
 *       "EPD_5IN65F_Display_part(const UBYTE *image, UWORD xstart, UWORD ystart, UWORD image_width, UWORD image_heigh)"
 *     ],
 *     "Display_Fast": [],
 *     "Display_Misc": [],
 *     "Sleep": [
 *       "EPD_5IN65F_Sleep()"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "The display supports a variety of colors including black, green, blue, red, yellow, and orange as
 * indicated by the defined color indices. White was ignored based on instructions since it does not offer a unique
 * channel but falls under black. The 'clean' color was not included in SupportedColorChannels since it was marked as
 * unavailable and suggested for 'Afterimage' which is not suitable for regular color display. Function categorization
 * was based on their naming and assumed functionality.",
 *   "PaintScale": 7,
 *   "PaintRotation": 0,
 *   "BitmapFunction": "GUI_ReadBmp_RGB_7Color"
 * }
 */

#pragma once

#include "../EPD_Common.h"

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief 5.65inch e-paper
namespace EPD_5in65f {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_5in65f.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 600;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 448;

enum RefreshMode { Display = 0 };

class EPD_5in65f_DrawTarget : public _7Color4BitEPD {
  public:
    std::string GetDeviceName() const override { return "5.65inch e-paper"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }

    // The following functions were not created:

    //  ! EPD_5IN65F_Display_part(const UBYTE *image, UWORD xstart, UWORD ystart, UWORD image_width, UWORD image_heigh) was
    //  skipped because I'm not sure what arguments to pass in!

    /// @brief Initialize the display
    void Init() { controller::EPD_Init(); }

    /// @brief Initialize the display
    void Init2() { controller::EPD_5IN65F_Init(); }

    /// @brief Clear the display
    void Clear() { controller::EPD_5IN65F_Clear(0x1); }

    /// @brief Put the display to sleep
    void Sleep() { controller::EPD_5IN65F_Sleep(); }

    /// @brief Display pixels in buffers to display
    void Display() { controller::EPD_5IN65F_Display(packedBits); }

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

    EPD_5in65f_DrawTarget(bool initializeSPI = true) : _7Color4BitEPD(GetWidth(), GetHeight(), initializeSPI) {}
    ~EPD_5in65f_DrawTarget() {}
};

} // namespace EPD_5in65f

} // namespace devices

} // namespace epaperapi