/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 1.54inch e-paper b V2
 * Shortname: EPD_1in54b_V2
 * Generated On: 26 April 2025 @ 5:06 PM
 * Supported Color Channels: black,red
 * Type: RedBlack1BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "1.54inch e-paper b V2",
 *   "ScreenWidth": 200,
 *   "ScreenHeight": 200,
 *   "SupportedColorChannels": [
 *     "black",
 *     "red"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_1IN54B_V2_Init(void)"
 *     ],
 *     "Clear": [
 *       "EPD_1IN54B_V2_Clear(void)"
 *     ],
 *     "Display": [
 *       "EPD_1IN54B_V2_Display(const UBYTE *blackimage, const UBYTE *redimage)"
 *     ],
 *     "Display_Base": [],
 *     "Display_Partial": [],
 *     "Display_Fast": [],
 *     "Display_Misc": [],
 *     "Sleep": [
 *       "EPD_1IN54B_V2_Sleep(void)"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "The display function EPD_1IN54B_V2_Display deals with two color channels: black and red. Thus, they were
 * chosen for the SupportedColorChannels. No occurrence of gray or white was noted, so no deductions were made in the
 * color channels for those cases.",
 *   "PaintRotation": 90,
 *   "BitmapFunction": "GUI_ReadBmp"
 * }
 */
 
#pragma once

#include "../EPD_Common.h"

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief 1.54inch e-paper b V2
namespace EPD_1in54b_V2 {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_1in54b_V2.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 200;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 200;

enum RefreshMode { Display = 0 };

class EPD_1in54b_V2_DrawTarget : public RedBlack1BitEPD {
  public:
    std::string GetDeviceName() const override { return "1.54inch e-paper b V2"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }
    
    /// @brief Initialize the display
    void Init() {
        controller::EPD_1IN54B_V2_Init();
    }

    /// @brief Clear the display
    void Clear() {
        controller::EPD_1IN54B_V2_Clear();
    }

    /// @brief Put the display to sleep
    void Sleep() {
        controller::EPD_1IN54B_V2_Sleep();
    }

    /// @brief Display pixels in buffers to display
    void Display() {
        controller::EPD_1IN54B_V2_Display(packedBitsBlack, packedBitsRed);
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

    EPD_1in54b_V2_DrawTarget(bool initializeSPI = true) : RedBlack1BitEPD(GetWidth(), GetHeight(), initializeSPI) {}
    ~EPD_1in54b_V2_DrawTarget() {}
};

} // namespace EPD_1in54b_V2

} // namespace devices

} // namespace epaperapi