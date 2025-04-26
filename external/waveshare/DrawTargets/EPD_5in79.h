/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 5.79inch e-paper
 * Shortname: EPD_5in79
 * Generated On: 26 April 2025 @ 5:41 PM
 * Supported Color Channels: black
 * Type: Black1BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "5.79inch e-paper",
 *   "ScreenWidth": 792,
 *   "ScreenHeight": 272,
 *   "SupportedColorChannels": [
 *     "black"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_5in79_Init(void)",
 *       "EPD_5in79_Init_Fast(void)",
 *       "EPD_5in79_Init_Partial(void)",
 *       "EPD_5in79_Init_4Gray(void)"
 *     ],
 *     "Clear": [
 *       "EPD_5in79_Clear(void)",
 *       "EPD_5in79_Clear_Black(void)"
 *     ],
 *     "Display": [
 *       "EPD_5in79_Display(const UBYTE *Image)"
 *     ],
 *     "Display_Base": [
 *       "EPD_5in79_Display_Base(const UBYTE *Image)"
 *     ],
 *     "Display_Partial": [
 *       "EPD_5in79_Display_Partial(const UBYTE *Image, UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend)"
 *     ],
 *     "Display_Fast": [
 *       "EPD_5in79_Display_Fast(const UBYTE *Image)"
 *     ],
 *     "Display_Misc": [
 *       "EPD_5in79_4GrayDisplay(UBYTE *Image)",
 *       "EPD_5in79_Display_Base_color(UBYTE color)"
 *     ],
 *     "Sleep": [
 *       "EPD_5in79_Sleep(void)"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "The function EPD_5in79_Display_Base_color indicates color support but it's not specified which colors, so
 * it's general. The gray functions suggest grayscale support covered under 'black'.",
 *   "PaintScale": 2,
 *   "PaintRotation": 0,
 *   "BitmapFunction": "GUI_ReadBmp"
 * }
 */

#pragma once

#include "../EPD_Common.h"

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief 5.79inch e-paper
namespace EPD_5in79 {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_5in79.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 792;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 272;

enum RefreshMode { Display = 0, Base = 1, Display2 = 2, Base_color = 3, Fast = 4 };

class EPD_5in79_DrawTarget : public Black1BitEPD {
  public:
    std::string GetDeviceName() const override { return "5.79inch e-paper"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }

    // The following functions were not created:

    //  ! EPD_5in79_Display_Partial(const UBYTE *Image, UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend) was skipped
    //  because I'm not sure what arguments to pass in!

    /// @brief Initialize the display
    void Init() { controller::EPD_5in79_Init(); }

    /// @brief Initialize the display
    void Init_Fast() { controller::EPD_5in79_Init_Fast(); }

    /// @brief Initialize the display
    void Init_4Gray() { controller::EPD_5in79_Init_4Gray(); }

    /// @brief Initialize the display
    void Init_Partial() { controller::EPD_5in79_Init_Partial(); }

    /// @brief Clear the display
    void Clear() { controller::EPD_5in79_Clear(); }

    /// @brief Clear the display
    void Clear_Black() { controller::EPD_5in79_Clear_Black(); }

    /// @brief Put the display to sleep
    void Sleep() { controller::EPD_5in79_Sleep(); }

    /// @brief Display pixels in buffers to display
    void Display() { controller::EPD_5in79_4GrayDisplay(packedBits); }

    /// @brief Display pixels in buffers to display
    void Display2() { controller::EPD_5in79_Display(packedBits); }

    /// @brief Display pixels in buffers to display
    void Display_Base_color() { controller::EPD_5in79_Display_Base_color(0); }

    /// @brief Display pixels in buffers to display
    void Display_Base() { controller::EPD_5in79_Display_Base(packedBits); }

    /// @brief Display pixels in buffers to display
    void Display_Fast() { controller::EPD_5in79_Display_Fast(packedBits); }

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

        case RefreshMode::Display2:
            Display2();
            break;

        case RefreshMode::Base_color:
            Display_Base_color();
            break;

        case RefreshMode::Base:
            Display_Base();
            break;

        case RefreshMode::Fast:
            Display_Fast();
            break;

        default:
            throw UnsupportedRefreshMode(mode, GetDeviceName());
        }
    }

    EPD_5in79_DrawTarget(bool initializeSPI = true) : Black1BitEPD(GetWidth(), GetHeight(), initializeSPI) {}
    ~EPD_5in79_DrawTarget() {}
};

} // namespace EPD_5in79

} // namespace devices

} // namespace epaperapi