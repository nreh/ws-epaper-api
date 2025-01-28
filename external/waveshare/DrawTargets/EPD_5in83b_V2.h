/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 5.83inch e-paper V2
 * Shortname: EPD_5in83b_V2
 * Generated On: 27 January 2025 @ 5:09 AM
 * Supported Color Channels: red,black
 * Type: RedBlack1BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "5.83inch e-paper V2",
 *   "ScreenWidth": 648,
 *   "ScreenHeight": 480,
 *   "SupportedColorChannels": [
 *     "red",
 *     "black"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_5IN83B_V2_Init()"
 *     ],
 *     "Clear": [
 *       "EPD_5IN83B_V2_Clear()"
 *     ],
 *     "Display": [
 *       "EPD_5IN83B_V2_Display(const UBYTE *blackimage, const UBYTE *ryimage)"
 *     ],
 *     "Display_Base": [],
 *     "Display_Partial": [],
 *     "Display_Fast": [],
 *     "Display_Misc": [],
 *     "Sleep": [
 *       "EPD_5IN83B_V2_Sleep()"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "The display function supports two channels, hence 'red' and 'black' are used. Functions are categorized
 * based on their names and expected behavior.",
 *   "PaintRotation": 0,
 *   "BitmapFunction": "GUI_ReadBmp"
 * }
 */
 
#pragma once

#include "../EPD_Common.h"

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief 5.83inch e-paper V2
namespace EPD_5in83b_V2 {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_5in83b_V2.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 648;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 480;

enum RefreshMode { Display = 0 };

class EPD_5in83b_V2_DrawTarget : public RedBlack1BitEPD {
  public:
    std::string GetDeviceName() const override { return "5.83inch e-paper V2"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }
    
    /// @brief Initialize the display
    void Init() {
        controller::EPD_5IN83B_V2_Init();
    }

    /// @brief Clear the display
    void Clear() {
        controller::EPD_5IN83B_V2_Clear();
    }

    /// @brief Put the display to sleep
    void Sleep() {
        controller::EPD_5IN83B_V2_Sleep();
    }

    /// @brief Display pixels in buffers to display
    void Display() {
        controller::EPD_5IN83B_V2_Display(packedBitsBlack, packedBitsRed);
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

    EPD_5in83b_V2_DrawTarget(bool initializeSPI = true) : RedBlack1BitEPD(GetWidth(), GetHeight(), initializeSPI) {}
    ~EPD_5in83b_V2_DrawTarget() {}
};

} // namespace EPD_5in83b_V2

} // namespace devices

} // namespace epaperapi