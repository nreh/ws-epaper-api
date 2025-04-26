/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 2.9inch e-paper b V4
 * Shortname: EPD_2in9b_V4
 * Generated On: 26 April 2025 @ 5:41 PM
 * Supported Color Channels: red,black
 * Type: RedBlack1BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "2.9inch e-paper b V4",
 *   "ScreenWidth": 128,
 *   "ScreenHeight": 296,
 *   "SupportedColorChannels": [
 *     "red",
 *     "black"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_2IN9B_V4_Init()",
 *       "EPD_2IN9B_V4_Init_Fast()"
 *     ],
 *     "Clear": [
 *       "EPD_2IN9B_V4_Clear()",
 *       "EPD_2IN9B_V4_Clear_Fast()",
 *       "EPD_2IN9B_V4_Clear_Black_Fast()",
 *       "EPD_2IN9B_V4_Clear_Red_Fast()"
 *     ],
 *     "Display": [
 *       "EPD_2IN9B_V4_Display(const UBYTE *blackimage, const UBYTE *ryimage)"
 *     ],
 *     "Display_Base": [
 *       "EPD_2IN9B_V4_Display_Base(const UBYTE *blackimage, const UBYTE *ryimage)"
 *     ],
 *     "Display_Partial": [
 *       "EPD_2IN9B_V4_Display_Partial(const UBYTE *Image, UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend)"
 *     ],
 *     "Display_Fast": [
 *       "EPD_2IN9B_V4_Display_Fast(const UBYTE *blackimage, const UBYTE *ryimage)"
 *     ],
 *     "Display_Misc": [],
 *     "Sleep": [
 *       "EPD_2IN9B_V4_Sleep()"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "Based on the function signatures, 'red' and 'black' color channels are assumed. Function categorization
 * is based on prefixes and implied functionality.",
 *   "PaintScale": 2,
 *   "PaintRotation": 270,
 *   "BitmapFunction": "GUI_ReadBmp"
 * }
 */

#pragma once

#include "../EPD_Common.h"

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief 2.9inch e-paper b V4
namespace EPD_2in9b_V4 {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_2in9b_V4.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 128;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 296;

enum RefreshMode { Display = 0, Base = 1, Fast = 2 };

class EPD_2in9b_V4_DrawTarget : public RedBlack1BitEPD {
  public:
    std::string GetDeviceName() const override { return "2.9inch e-paper b V4"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }

    // The following functions were not created:

    //  ! EPD_2IN9B_V4_Display_Partial(const UBYTE *Image, UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend) was skipped
    //  because I'm not sure what arguments to pass in!

    /// @brief Initialize the display
    void Init() { controller::EPD_2IN9B_V4_Init(); }

    /// @brief Initialize the display
    void Init_Fast() { controller::EPD_2IN9B_V4_Init_Fast(); }

    /// @brief Clear the display
    void Clear() { controller::EPD_2IN9B_V4_Clear(); }

    /// @brief Clear the display
    void Clear_Fast() { controller::EPD_2IN9B_V4_Clear_Fast(); }

    /// @brief Clear the display
    void Clear_Red_Fast() { controller::EPD_2IN9B_V4_Clear_Red_Fast(); }

    /// @brief Clear the display
    void Clear_Black_Fast() { controller::EPD_2IN9B_V4_Clear_Black_Fast(); }

    /// @brief Put the display to sleep
    void Sleep() { controller::EPD_2IN9B_V4_Sleep(); }

    /// @brief Display pixels in buffers to display
    void Display() { controller::EPD_2IN9B_V4_Display(packedBitsBlack, packedBitsRed); }

    /// @brief Display pixels in buffers to display
    void Display_Base() { controller::EPD_2IN9B_V4_Display_Base(packedBitsBlack, packedBitsRed); }

    /// @brief Display pixels in buffers to display
    void Display_Fast() { controller::EPD_2IN9B_V4_Display_Fast(packedBitsBlack, packedBitsRed); }

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

    EPD_2in9b_V4_DrawTarget(bool initializeSPI = true) : RedBlack1BitEPD(GetWidth(), GetHeight(), initializeSPI) {}
    ~EPD_2in9b_V4_DrawTarget() {}
};

} // namespace EPD_2in9b_V4

} // namespace devices

} // namespace epaperapi