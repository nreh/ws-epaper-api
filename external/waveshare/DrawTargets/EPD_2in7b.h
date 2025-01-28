/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 2.7inch e-paper b
 * Shortname: EPD_2in7b
 * Generated On: 27 January 2025 @ 5:09 AM
 * Supported Color Channels: black,red
 * Type: RedBlack1BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "2.7inch e-paper b",
 *   "ScreenWidth": 176,
 *   "ScreenHeight": 264,
 *   "SupportedColorChannels": [
 *     "black",
 *     "red"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_2IN7B_Init()"
 *     ],
 *     "Clear": [
 *       "EPD_2IN7B_Clear()"
 *     ],
 *     "Display": [
 *       "EPD_2IN7B_Display(UBYTE *Imageblack, UBYTE *Imagered)"
 *     ],
 *     "Display_Base": [],
 *     "Display_Partial": [],
 *     "Display_Fast": [],
 *     "Display_Misc": [],
 *     "Sleep": [
 *       "EPD_2IN7B_Sleep()"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "The display supports two color channels: black and red, deduced from the dual arguments in
 * EPD_2IN7B_Display(UBYTE *Imageblack, UBYTE *Imagered). No mention of additional color channels or gray/white colors
 * was found, so the assumption of black and red stands.",
 *   "PaintRotation": 270,
 *   "BitmapFunction": "GUI_ReadBmp"
 * }
 */
 
#pragma once

#include "../EPD_Common.h"

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief 2.7inch e-paper b
namespace EPD_2in7b {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_2in7b.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 176;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 264;

enum RefreshMode { Display = 0 };

class EPD_2in7b_DrawTarget : public RedBlack1BitEPD {
  public:
    std::string GetDeviceName() const override { return "2.7inch e-paper b"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }
    
    /// @brief Initialize the display
    void Init() {
        controller::EPD_2IN7B_Init();
    }

    /// @brief Clear the display
    void Clear() {
        controller::EPD_2IN7B_Clear();
    }

    /// @brief Put the display to sleep
    void Sleep() {
        controller::EPD_2IN7B_Sleep();
    }

    /// @brief Display pixels in buffers to display
    void Display() {
        controller::EPD_2IN7B_Display(packedBitsBlack, packedBitsRed);
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

    EPD_2in7b_DrawTarget(bool initializeSPI = true) : RedBlack1BitEPD(GetWidth(), GetHeight(), initializeSPI) {}
    ~EPD_2in7b_DrawTarget() {}
};

} // namespace EPD_2in7b

} // namespace devices

} // namespace epaperapi