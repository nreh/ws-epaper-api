/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 5.84inch e-paper
 * Shortname: EPD_5in84
 * Generated On: 26 April 2025 @ 5:41 PM
 * Supported Color Channels: black
 * Type: Black1BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "5.84inch e-paper",
 *   "ScreenWidth": 768,
 *   "ScreenHeight": 256,
 *   "SupportedColorChannels": [
 *     "black"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_5in84_Init()"
 *     ],
 *     "Clear": [
 *       "EPD_5in84_Clear()"
 *     ],
 *     "Display": [
 *       "EPD_5in84_Display(UBYTE *Image)"
 *     ],
 *     "Display_Base": [],
 *     "Display_Partial": [],
 *     "Display_Fast": [],
 *     "Display_Misc": [],
 *     "Sleep": [
 *       "EPD_5in84_Sleep()"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "The header does not specify additional colors, so 'black' is assumed from the single image parameter in
 * the display function. Functions were categorized based on typical e-paper operations.",
 *   "PaintRotation": 0,
 *   "BitmapFunction": "GUI_ReadBmp"
 * }
 */
 
#pragma once

#include "../EPD_Common.h"

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief 5.84inch e-paper
namespace EPD_5in84 {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_5in84.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 768;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 256;

enum RefreshMode { Display = 0 };

class EPD_5in84_DrawTarget : public Black1BitEPD {
  public:
    std::string GetDeviceName() const override { return "5.84inch e-paper"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }
    
    /// @brief Initialize the display
    void Init() {
        controller::EPD_5in84_Init();
    }

    /// @brief Clear the display
    void Clear() {
        controller::EPD_5in84_Clear();
    }

    /// @brief Put the display to sleep
    void Sleep() {
        controller::EPD_5in84_Sleep();
    }

    /// @brief Display pixels in buffers to display
    void Display() {
        controller::EPD_5in84_Display(packedBits);
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

    EPD_5in84_DrawTarget(bool initializeSPI = true) : Black1BitEPD(GetWidth(), GetHeight(), initializeSPI) {}
    ~EPD_5in84_DrawTarget() {}
};

} // namespace EPD_5in84

} // namespace devices

} // namespace epaperapi