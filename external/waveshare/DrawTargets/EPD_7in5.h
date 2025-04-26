/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 7.5inch e-paper
 * Shortname: EPD_7in5
 * Generated On: 26 April 2025 @ 5:06 PM
 * Supported Color Channels: black
 * Type: Black1BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "7.5inch e-paper",
 *   "ScreenWidth": 640,
 *   "ScreenHeight": 384,
 *   "SupportedColorChannels": [
 *     "black"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_7IN5_Init()"
 *     ],
 *     "Clear": [
 *       "EPD_7IN5_Clear()"
 *     ],
 *     "Display": [
 *       "EPD_7IN5_Display(UBYTE *Image)"
 *     ],
 *     "Display_Base": [],
 *     "Display_Partial": [],
 *     "Display_Fast": [],
 *     "Display_Misc": [],
 *     "Sleep": [
 *       "EPD_7IN5_Sleep()"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "The display uses a single channel, assumed to be 'black', as indicated by the argument in
 * EPD_7IN5_Display(). No additional colors like red or blue are mentioned, suggesting it only supports the black color
 * channel.",
 *   "PaintRotation": 0,
 *   "BitmapFunction": "GUI_ReadBmp"
 * }
 */
 
#pragma once

#include "../EPD_Common.h"

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief 7.5inch e-paper
namespace EPD_7in5 {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_7in5.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 640;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 384;

enum RefreshMode { Display = 0 };

class EPD_7in5_DrawTarget : public Black1BitEPD {
  public:
    std::string GetDeviceName() const override { return "7.5inch e-paper"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }
    
    /// @brief Initialize the display
    void Init() {
        controller::EPD_7IN5_Init();
    }

    /// @brief Clear the display
    void Clear() {
        controller::EPD_7IN5_Clear();
    }

    /// @brief Put the display to sleep
    void Sleep() {
        controller::EPD_7IN5_Sleep();
    }

    /// @brief Display pixels in buffers to display
    void Display() {
        controller::EPD_7IN5_Display(packedBits);
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

    EPD_7in5_DrawTarget(bool initializeSPI = true) : Black1BitEPD(GetWidth(), GetHeight(), initializeSPI) {}
    ~EPD_7in5_DrawTarget() {}
};

} // namespace EPD_7in5

} // namespace devices

} // namespace epaperapi