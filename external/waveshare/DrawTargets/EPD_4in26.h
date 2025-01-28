/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 4.26inch e-paper
 * Shortname: EPD_4in26
 * Generated On: 27 January 2025 @ 5:09 AM
 * Supported Color Channels: black
 * Type: Black2BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "4.26inch e-paper",
 *   "ScreenWidth": 800,
 *   "ScreenHeight": 480,
 *   "SupportedColorChannels": [
 *     "black"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_4in26_Init()",
 *       "EPD_4in26_Init_Fast()",
 *       "EPD_4in26_Init_4GRAY()"
 *     ],
 *     "Clear": [
 *       "EPD_4in26_Clear()"
 *     ],
 *     "Display": [
 *       "EPD_4in26_Display(UBYTE *Image)"
 *     ],
 *     "Display_Base": [
 *       "EPD_4in26_Display_Base(UBYTE *Image)"
 *     ],
 *     "Display_Partial": [
 *       "EPD_4in26_Display_Part(UBYTE *Image, UWORD x, UWORD y, UWORD w, UWORD l)"
 *     ],
 *     "Display_Fast": [
 *       "EPD_4in26_Display_Fast(UBYTE *Image)"
 *     ],
 *     "Display_Misc": [
 *       "EPD_4in26_4GrayDisplay(UBYTE *Image)"
 *     ],
 *     "Sleep": [
 *       "EPD_4in26_Sleep()"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "The header suggests 'black' as the color channel due to its typical use. The function
 * EPD_4in26_4GrayDisplay indicates 4-gray scale support, but gray is classified under 'black'. Functions were
 * categorized based on naming and presumed use.",
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

/// @brief 4.26inch e-paper
namespace EPD_4in26 {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_4in26.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 800;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 480;

enum RefreshMode { Display = 0, Base = 1, Fast = 2, EPD_4in26_4GrayDisplay = 3 };

class EPD_4in26_DrawTarget : public Black2BitEPD {
  public:
    std::string GetDeviceName() const override { return "4.26inch e-paper"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }
    
    // The following functions were not created:

    //  ! EPD_4in26_Display_Part(UBYTE *Image, UWORD x, UWORD y, UWORD w, UWORD l) was skipped because I'm not sure what arguments to pass in!

    /// @brief Initialize the display
    void Init() {
        controller::EPD_4in26_Init();
    }

    /// @brief Initialize the display
    void Init_Fast() {
        controller::EPD_4in26_Init_Fast();
    }

    /// @brief Initialize the display
    void Init_4GRAY() {
        controller::EPD_4in26_Init_4GRAY();
    }

    /// @brief Clear the display
    void Clear() {
        controller::EPD_4in26_Clear();
    }

    /// @brief Put the display to sleep
    void Sleep() {
        controller::EPD_4in26_Sleep();
    }

    /// @brief Display pixels in 1 bit buffer to display
    void Display() {
        controller::EPD_4in26_Display(packedBits_1bit);
    }

    /// @brief Display pixels in 1 bit buffer to display
    void Display_Base() {
        controller::EPD_4in26_Display_Base(packedBits_1bit);
    }

    /// @brief Display pixels in 1 bit buffer to display
    void Display_Fast() {
        controller::EPD_4in26_Display_Fast(packedBits_1bit);
    }

    /// @brief Display pixels in 2 bit buffer to display (4 shades of gray)
    void EPD_4in26_4GrayDisplay() {
        controller::EPD_4in26_4GrayDisplay(packedBits_2bit);
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

        case RefreshMode::Base:
        Display_Base();
        break;

        case RefreshMode::Fast:
        Display_Fast();
        break;

        case RefreshMode::EPD_4in26_4GrayDisplay:
        EPD_4in26_4GrayDisplay();
        break;


        default:
            throw UnsupportedRefreshMode(mode, GetDeviceName());
        }
        
    }

    EPD_4in26_DrawTarget(bool initializeSPI = true) : Black2BitEPD(GetWidth(), GetHeight(), initializeSPI) {}
    ~EPD_4in26_DrawTarget() {}
};

} // namespace EPD_4in26

} // namespace devices

} // namespace epaperapi