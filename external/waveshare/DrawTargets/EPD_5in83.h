/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 5.83inch e-paper
 * Shortname: EPD_5in83
 * Generated On: 26 April 2025 @ 5:41 PM
 * Supported Color Channels: black
 * Type: Black1BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "5.83inch e-paper",
 *   "ScreenWidth": 600,
 *   "ScreenHeight": 448,
 *   "SupportedColorChannels": [
 *     "black"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_5IN83_Init()"
 *     ],
 *     "Clear": [
 *       "EPD_5IN83_Clear()"
 *     ],
 *     "Display": [
 *       "EPD_5IN83_Display(UBYTE *Image)"
 *     ],
 *     "Display_Base": [],
 *     "Display_Partial": [],
 *     "Display_Fast": [],
 *     "Display_Misc": [],
 *     "Sleep": [
 *       "EPD_5IN83_Sleep()"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "The display uses a single channel, presumed to be 'black', as indicated by the argument in
 * EPD_5IN83_Display(). No additional color information (such as red or blue) is provided, suggesting this display only
 * supports the black color channel.",
 *   "PaintRotation": 180,
 *   "BitmapFunction": "GUI_ReadBmp"
 * }
 */
 
#pragma once

#include "../EPD_Common.h"

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief 5.83inch e-paper
namespace EPD_5in83 {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_5in83.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 600;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 448;

enum RefreshMode { Display = 0 };

class EPD_5in83_DrawTarget : public Black1BitEPD {
  public:
    std::string GetDeviceName() const override { return "5.83inch e-paper"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }
    
    /// @brief Initialize the display
    void Init() {
        controller::EPD_5IN83_Init();
    }

    /// @brief Clear the display
    void Clear() {
        controller::EPD_5IN83_Clear();
    }

    /// @brief Put the display to sleep
    void Sleep() {
        controller::EPD_5IN83_Sleep();
    }

    /// @brief Display pixels in buffers to display
    void Display() {
        controller::EPD_5IN83_Display(packedBits);
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

    EPD_5in83_DrawTarget(bool initializeSPI = true) : Black1BitEPD(GetWidth(), GetHeight(), initializeSPI) {}
    ~EPD_5in83_DrawTarget() {}
};

} // namespace EPD_5in83

} // namespace devices

} // namespace epaperapi