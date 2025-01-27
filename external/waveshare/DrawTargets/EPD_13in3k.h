/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 13.3inch e-paper (K)
 * Shortname: EPD_13in3k
 * Generated On: 27 January 2025 @ 2:59 AM
 * Supported Color Channels: black
 * Type: Black2BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "13.3inch e-paper (K)",
 *   "ScreenWidth": 960,
 *   "ScreenHeight": 680,
 *   "SupportedColorChannels": [
 *     "black"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_13IN3K_Init(void)",
 *       "EPD_13IN3K_Init_Part(void)",
 *       "EPD_13IN3K_Init_4GRAY(void)"
 *     ],
 *     "Clear": [
 *       "EPD_13IN3K_Clear(void)"
 *     ],
 *     "Display": [
 *       "EPD_13IN3K_Display(UBYTE *Image)"
 *     ],
 *     "Display_Base": [
 *       "EPD_13IN3K_Display_Base(UBYTE *Image)"
 *     ],
 *     "Display_Partial": [
 *       "EPD_13IN3K_Display_Part(UBYTE *Image, UWORD x, UWORD y, UWORD w, UWORD l)"
 *     ],
 *     "Display_Fast": [],
 *     "Display_Misc": [
 *       "EPD_13IN3K_color_Base(UBYTE color)",
 *       "EPD_13IN3K_4GrayDisplay(UBYTE *Image)"
 *     ],
 *     "Sleep": [
 *       "EPD_13IN3K_Sleep(void)"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "The function EPD_13IN3K_Display only accepts a single image, assumed to be 'black'. The
 * EPD_13IN3K_Init_4GRAY and EPD_13IN3K_4GrayDisplay functions mention gray, but as per instructions, 'gray' is treated
 * as part of the 'black' channel. EPD_13IN3K_color_Base and EPD_13IN3K_4GrayDisplay were categorized under Display_Misc
 * due to their specific purposes for handling color and grayscale display.",
 *   "PaintScale": 4,
 *   "PaintRotation": 0,
 *   "BitmapFunction": "GUI_ReadBmp"
 * }
 */
 
#pragma once

#include "../EPD_Common.h"

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief 13.3inch e-paper (K)
namespace EPD_13in3k {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_13in3k.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 960;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 680;

enum RefreshMode { Display = 0, Base = 1, EPD_13IN3K_color_Base = 2, EPD_13IN3K_4GrayDisplay = 3 };

class EPD_13in3k_DrawTarget : public Black2BitEPD {
  public:
    std::string GetDeviceName() const override { return "13.3inch e-paper (K)"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }
    
    // The following functions were not created:

    //  ! EPD_13IN3K_Display_Part(UBYTE *Image, UWORD x, UWORD y, UWORD w, UWORD l) was skipped because I'm not sure what arguments to pass in!

    /// @brief Initialize the display
    void Init() {
        controller::EPD_13IN3K_Init();
    }

    /// @brief Initialize the display
    void Init_Part() {
        controller::EPD_13IN3K_Init_Part();
    }

    /// @brief Initialize the display
    void Init_4GRAY() {
        controller::EPD_13IN3K_Init_4GRAY();
    }

    /// @brief Clear the display
    void Clear() {
        controller::EPD_13IN3K_Clear();
    }

    /// @brief Put the display to sleep
    void Sleep() {
        controller::EPD_13IN3K_Sleep();
    }

    /// @brief Display pixels in 1 bit buffer to display
    void Display() {
        controller::EPD_13IN3K_Display(packedBits_1bit);
    }

    /// @brief Display pixels in 1 bit buffer to display
    void EPD_13IN3K_color_Base() {
        controller::EPD_13IN3K_color_Base(packedBits_1bit);
    }

    /// @brief Display pixels in 1 bit buffer to display
    void Display_Base() {
        controller::EPD_13IN3K_Display_Base(packedBits_1bit);
    }

    /// @brief Display pixels in 2 bit buffer to display (4 shades of gray)
    void EPD_13IN3K_4GrayDisplay() {
        controller::EPD_13IN3K_4GrayDisplay(packedBits_2bit);
    }

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

        case RefreshMode::EPD_13IN3K_color_Base:
        EPD_13IN3K_color_Base();
        break;

        case RefreshMode::Base:
        Display_Base();
        break;

        case RefreshMode::EPD_13IN3K_4GrayDisplay:
        EPD_13IN3K_4GrayDisplay();
        break;


        default:
            throw UnsupportedRefreshMode(mode, GetDeviceName());
        }
        
    }

    EPD_13in3k_DrawTarget() : Black2BitEPD(GetWidth(), GetHeight()) {}
    ~EPD_13in3k_DrawTarget() {}
};

} // namespace EPD_13in3k

} // namespace devices

} // namespace epaperapi