/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 10.2inch b e-paper
 * Shortname: EPD_10in2b
 * Generated On: 26 April 2025 @ 5:41 PM
 * Supported Color Channels: black,red
 * Type: RedBlack1BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "10.2inch b e-paper",
 *   "ScreenWidth": 960,
 *   "ScreenHeight": 640,
 *   "SupportedColorChannels": [
 *     "black",
 *     "red"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_10IN2b_Init(void)"
 *     ],
 *     "Clear": [
 *       "EPD_10IN2b_Clear(void)"
 *     ],
 *     "Display": [
 *       "EPD_10IN2b_Display(UBYTE *Image, UBYTE *RedImage)"
 *     ],
 *     "Display_Base": [],
 *     "Display_Partial": [],
 *     "Display_Fast": [],
 *     "Display_Misc": [],
 *     "Sleep": [
 *       "EPD_10IN2b_Sleep(void)"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "This display supports black and red, as indicated by the use of dual channel images in the
 * EPD_10IN2b_Display function. The naming 'RedImage' clearly denotes this functionality.",
 *   "PaintRotation": 0,
 *   "BitmapFunction": "GUI_ReadBmp"
 * }
 */
 
#pragma once

#include "../EPD_Common.h"

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief 10.2inch b e-paper
namespace EPD_10in2b {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_10in2b.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 960;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 640;

enum RefreshMode { Display = 0 };

class EPD_10in2b_DrawTarget : public RedBlack1BitEPD {
  public:
    std::string GetDeviceName() const override { return "10.2inch b e-paper"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }
    
    /// @brief Initialize the display
    void Init() {
        controller::EPD_10IN2b_Init();
    }

    /// @brief Clear the display
    void Clear() {
        controller::EPD_10IN2b_Clear();
    }

    /// @brief Put the display to sleep
    void Sleep() {
        controller::EPD_10IN2b_Sleep();
    }

    /// @brief Display pixels in buffers to display
    void Display() {
        controller::EPD_10IN2b_Display(packedBitsBlack, packedBitsRed);
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

    EPD_10in2b_DrawTarget(bool initializeSPI = true) : RedBlack1BitEPD(GetWidth(), GetHeight(), initializeSPI) {}
    ~EPD_10in2b_DrawTarget() {}
};

} // namespace EPD_10in2b

} // namespace devices

} // namespace epaperapi