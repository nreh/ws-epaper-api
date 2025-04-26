/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 4.37inch e-paper b
 * Shortname: EPD_4in37b
 * Generated On: 26 April 2025 @ 5:41 PM
 * Supported Color Channels: black,red
 * Type: RedBlack1BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "4.37inch e-paper b",
 *   "ScreenWidth": 176,
 *   "ScreenHeight": 480,
 *   "SupportedColorChannels": [
 *     "black",
 *     "red"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_4IN37B_Init()"
 *     ],
 *     "Clear": [
 *       "EPD_4IN37B_Clear()"
 *     ],
 *     "Display": [
 *       "EPD_4IN37B_Display(UBYTE *ImageBlack, UBYTE*ImageRed)"
 *     ],
 *     "Display_Base": [],
 *     "Display_Partial": [
 *       "EPD_4IN37B_Display_Part(UBYTE *ImageBlack, UBYTE*ImageRed, UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD
 * Yend)"
 *     ],
 *     "Display_Fast": [],
 *     "Display_Misc": [],
 *     "Sleep": [
 *       "EPD_4IN37B_Sleep()"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "The display supports two color channels: black and red, derived from the arguments in EPD_4IN37B_Display
 * and EPD_4IN37B_Display_Part functions. The function names and parameters clearly indicate support for these two
 * specific channels.",
 *   "PaintRotation": 270,
 *   "BitmapFunction": "GUI_ReadBmp"
 * }
 */
 
#pragma once

#include "../EPD_Common.h"

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief 4.37inch e-paper b
namespace EPD_4in37b {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_4in37b.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 176;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 480;

enum RefreshMode { Display = 0 };

class EPD_4in37b_DrawTarget : public RedBlack1BitEPD {
  public:
    std::string GetDeviceName() const override { return "4.37inch e-paper b"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }
    
    // The following functions were not created:

    //  ! EPD_4IN37B_Display_Part(UBYTE *ImageBlack, UBYTE*ImageRed, UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend) was skipped because I'm not sure what arguments to pass in!

    /// @brief Initialize the display
    void Init() {
        controller::EPD_4IN37B_Init();
    }

    /// @brief Clear the display
    void Clear() {
        controller::EPD_4IN37B_Clear();
    }

    /// @brief Put the display to sleep
    void Sleep() {
        controller::EPD_4IN37B_Sleep();
    }

    /// @brief Display pixels in buffers to display
    void Display() {
        controller::EPD_4IN37B_Display(packedBitsBlack, packedBitsRed);
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


        default:
            throw UnsupportedRefreshMode(mode, GetDeviceName());
        }
        
    }

    EPD_4in37b_DrawTarget(bool initializeSPI = true) : RedBlack1BitEPD(GetWidth(), GetHeight(), initializeSPI) {}
    ~EPD_4in37b_DrawTarget() {}
};

} // namespace EPD_4in37b

} // namespace devices

} // namespace epaperapi