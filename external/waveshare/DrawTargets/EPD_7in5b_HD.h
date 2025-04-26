/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 7.5inch e-paper HD
 * Shortname: EPD_7in5b_HD
 * Generated On: 26 April 2025 @ 5:41 PM
 * Supported Color Channels: black,red
 * Type: RedBlack1BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "7.5inch e-paper HD",
 *   "ScreenWidth": 880,
 *   "ScreenHeight": 528,
 *   "SupportedColorChannels": [
 *     "black",
 *     "red"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_7IN5B_HD_Init(void)"
 *     ],
 *     "Clear": [
 *       "EPD_7IN5B_HD_Clear(void)",
 *       "EPD_7IN5B_HD_ClearRed(void)",
 *       "EPD_7IN5B_HD_ClearBlack(void)"
 *     ],
 *     "Display": [
 *       "EPD_7IN5B_HD_Display(const UBYTE *blackimage, const UBYTE *ryimage)"
 *     ],
 *     "Display_Base": [],
 *     "Display_Partial": [],
 *     "Display_Fast": [],
 *     "Display_Misc": [],
 *     "Sleep": [
 *       "EPD_7IN5B_HD_Sleep(void)"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "The function EPD_7IN5B_HD_Display indicates using separate channels for 'black' and 'red', which suggests
 * it supports these colors. Clear functions for specific 'red' and 'black' channels also confirm this. 'ryimage' in
 * Display function indicates possibly 'red/yellow', but 'red' is more commonly supported.",
 *   "PaintRotation": 0,
 *   "BitmapFunction": "GUI_ReadBmp"
 * }
 */
 
#pragma once

#include "../EPD_Common.h"

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief 7.5inch e-paper HD
namespace EPD_7in5b_HD {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_7in5b_HD.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 880;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 528;

enum RefreshMode { Display = 0 };

class EPD_7in5b_HD_DrawTarget : public RedBlack1BitEPD {
  public:
    std::string GetDeviceName() const override { return "7.5inch e-paper HD"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }
    
    /// @brief Initialize the display
    void Init() {
        controller::EPD_7IN5B_HD_Init();
    }

    /// @brief Clear the display
    void Clear() {
        controller::EPD_7IN5B_HD_Clear();
    }

    /// @brief Clear the display
    void ClearRed() {
        controller::EPD_7IN5B_HD_ClearRed();
    }

    /// @brief Clear the display
    void ClearBlack() {
        controller::EPD_7IN5B_HD_ClearBlack();
    }

    /// @brief Put the display to sleep
    void Sleep() {
        controller::EPD_7IN5B_HD_Sleep();
    }

    /// @brief Display pixels in buffers to display
    void Display() {
        controller::EPD_7IN5B_HD_Display(packedBitsBlack, packedBitsRed);
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

    EPD_7in5b_HD_DrawTarget(bool initializeSPI = true) : RedBlack1BitEPD(GetWidth(), GetHeight(), initializeSPI) {}
    ~EPD_7in5b_HD_DrawTarget() {}
};

} // namespace EPD_7in5b_HD

} // namespace devices

} // namespace epaperapi