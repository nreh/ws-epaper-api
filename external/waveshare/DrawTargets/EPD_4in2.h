/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 4.2inch e-paper
 * Shortname: EPD_4in2
 * Generated On: 27 January 2025 @ 5:09 AM
 * Supported Color Channels: black
 * Type: Black2BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "4.2inch e-paper",
 *   "ScreenWidth": 400,
 *   "ScreenHeight": 300,
 *   "SupportedColorChannels": [
 *     "black"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_4IN2_Init_Fast()",
 *       "EPD_4IN2_Init_Partial()",
 *       "EPD_4IN2_Init_4Gray()"
 *     ],
 *     "Clear": [
 *       "EPD_4IN2_Clear()"
 *     ],
 *     "Display": [
 *       "EPD_4IN2_Display(UBYTE *Image)",
 *       "EPD_4IN2_4GrayDisplay(const UBYTE *Image)"
 *     ],
 *     "Display_Base": [],
 *     "Display_Partial": [
 *       "EPD_4IN2_PartialDisplay(UWORD X_start, UWORD Y_start, UWORD X_end, UWORD Y_end, UBYTE *Image)"
 *     ],
 *     "Display_Fast": [],
 *     "Display_Misc": [],
 *     "Sleep": [
 *       "EPD_4IN2_Sleep()"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "The display supports black and grayscale as mentioned in the version log, but grayscale falls under the
 * established rule of not branching out to separate color channels. No additional colors like red or yellow are evident
 * in the display functions. Three initialization functions suggest versatility for fast, partial, and grayscale
 * operations. 'Grayscale' functions were categorically placed under Display as they still pertain to image
 * presentation. Grayscale does not warrant another color channel per instructions.",
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

/// @brief 4.2inch e-paper
namespace EPD_4in2 {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_4in2.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 400;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 300;

enum RefreshMode { Display = 0, EPD_4IN2_4GrayDisplay = 1 };

class EPD_4in2_DrawTarget : public Black2BitEPD {
  public:
    std::string GetDeviceName() const override { return "4.2inch e-paper"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }
    
    // The following functions were not created:

    //  ! EPD_4IN2_PartialDisplay(UWORD X_start, UWORD Y_start, UWORD X_end, UWORD Y_end, UBYTE *Image) was skipped because I'm not sure what arguments to pass in!

    /// @brief Initialize the display
    void Init() {
        controller::EPD_4IN2_Init_Fast();
    }

    /// @brief Initialize the display
    void Init_4Gray() {
        controller::EPD_4IN2_Init_4Gray();
    }

    /// @brief Initialize the display
    void Init_Partial() {
        controller::EPD_4IN2_Init_Partial();
    }

    /// @brief Clear the display
    void Clear() {
        controller::EPD_4IN2_Clear();
    }

    /// @brief Put the display to sleep
    void Sleep() {
        controller::EPD_4IN2_Sleep();
    }

    /// @brief Display pixels in 1 bit buffer to display
    void Display() {
        controller::EPD_4IN2_Display(packedBits_1bit);
    }

    /// @brief Display pixels in 2 bit buffer to display (4 shades of gray)
    void EPD_4IN2_4GrayDisplay() {
        controller::EPD_4IN2_4GrayDisplay(packedBits_2bit);
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

        case RefreshMode::EPD_4IN2_4GrayDisplay:
        EPD_4IN2_4GrayDisplay();
        break;


        default:
            throw UnsupportedRefreshMode(mode, GetDeviceName());
        }
        
    }

    EPD_4in2_DrawTarget(bool initializeSPI = true) : Black2BitEPD(GetWidth(), GetHeight(), initializeSPI) {}
    ~EPD_4in2_DrawTarget() {}
};

} // namespace EPD_4in2

} // namespace devices

} // namespace epaperapi