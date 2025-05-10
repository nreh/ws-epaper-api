/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 13.3inch e-paper (B) V1.0
 * Shortname: EPD_13in3b
 * Generated On: 26 April 2025 @ 5:41 PM
 * Supported Color Channels: black,red
 * Type: RedBlack1BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "13.3inch e-paper (B) V1.0",
 *   "ScreenWidth": 960,
 *   "ScreenHeight": 680,
 *   "SupportedColorChannels": [
 *     "black",
 *     "red"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_13IN3B_Init(void)"
 *     ],
 *     "Clear": [
 *       "EPD_13IN3B_Clear(void)",
 *       "EPD_13IN3B_Clear_Black(void)",
 *       "EPD_13IN3B_Clear_Red(void)"
 *     ],
 *     "Display": [
 *       "EPD_13IN3B_Display(const UBYTE *blackimage, const UBYTE *ryimage)"
 *     ],
 *     "Display_Base": [
 *       "EPD_13IN3B_Display_Base(const UBYTE *blackimage, const UBYTE *ryimage)",
 *       "EPD_13IN3B_Display_Base_White(void)"
 *     ],
 *     "Display_Partial": [
 *       "EPD_13IN3B_Display_Partial(const UBYTE *Image, UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend)"
 *     ],
 *     "Display_Fast": [],
 *     "Display_Misc": [],
 *     "Sleep": [
 *       "EPD_13IN3B_Sleep(void)"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "The EPD_13IN3B_Display function uses two images, assumed to be for 'black' and 'red', thus those channels
 * are used. The function EPD_13IN3B_Display_Base_White mentions 'White' but is included in 'Display_Base' for
 * functionality rather than color channel support. Other functions have clear categorization based on their names.",
 *   "PaintRotation": 0,
 *   "BitmapFunction": "GUI_ReadBmp"
 * }
 */

#pragma once

#include "../EPD_Common.h"

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief 13.3inch e-paper (B) V1.0
namespace EPD_13in3b {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_13in3b.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 960;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 680;

enum RefreshMode { Display = 0, Base = 1 };

class EPD_13in3b_DrawTarget : public RedBlack1BitEPD {
  public:
    std::string GetDeviceName() const override { return "13.3inch e-paper (B) V1.0"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }

    // The following functions were not created:

    //  ! EPD_13IN3B_Display_Partial(const UBYTE *Image, UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend) was skipped
    //  because I'm not sure what arguments to pass in!

    /// @brief Initialize the display
    void Init() { controller::EPD_13IN3B_Init(); }

    /// @brief Clear the display
    void Clear() { controller::EPD_13IN3B_Clear(); }

    /// @brief Clear the display
    void Clear_Red() { controller::EPD_13IN3B_Clear_Red(); }

    /// @brief Clear the display
    void Clear_Black() { controller::EPD_13IN3B_Clear_Black(); }

    /// @brief Put the display to sleep
    void Sleep() { controller::EPD_13IN3B_Sleep(); }

    /// @brief Display pixels in buffers to display
    void Display() { controller::EPD_13IN3B_Display(packedBitsBlack, packedBitsRed); }

    /// @brief Display pixels in buffers to display
    void Display_Base() { controller::EPD_13IN3B_Display_Base(packedBitsBlack, packedBitsRed); }

    /// @brief Display pixels in buffers to display
    // void Display_Base_White() { controller::EPD_13IN3B_Display_Base_White(); } //! Undefined

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

        default:
            throw UnsupportedRefreshMode(mode, GetDeviceName());
        }
    }

    EPD_13in3b_DrawTarget(bool initialize = true) : RedBlack1BitEPD(GetWidth(), GetHeight(), initialize) {
        if (initialize)
            Init();
    }
    ~EPD_13in3b_DrawTarget() {}
};

} // namespace EPD_13in3b

} // namespace devices

} // namespace epaperapi