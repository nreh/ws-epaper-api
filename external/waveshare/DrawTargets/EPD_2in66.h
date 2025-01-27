/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 2.66inch e-paper
 * Shortname: EPD_2in66
 * Generated On: 27 January 2025 @ 2:59 AM
 * Supported Color Channels: black
 * Type: Black1BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "2.66inch e-paper",
 *   "ScreenWidth": 152,
 *   "ScreenHeight": 296,
 *   "SupportedColorChannels": [
 *     "black"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_2IN66_Init(void)",
 *       "EPD_2IN66_Init_partial()"
 *     ],
 *     "Clear": [
 *       "EPD_2IN66_Clear(void)"
 *     ],
 *     "Display": [
 *       "EPD_2IN66_Display(UBYTE *Image)"
 *     ],
 *     "Display_Base": [],
 *     "Display_Partial": [],
 *     "Display_Fast": [],
 *     "Display_Misc": [],
 *     "Sleep": [
 *       "EPD_2IN66_Sleep(void)"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "The display functions suggest single-channel display capability with default support for 'black'. The
 * EPD_2IN66_Init_partial function suggests partial initialization or operation mode, which is not entirely clear.",
 *   "PaintRotation": 270,
 *   "BitmapFunction": "GUI_ReadBmp"
 * }
 */
 
#pragma once

#include "../EPD_Common.h"

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief 2.66inch e-paper
namespace EPD_2in66 {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_2in66.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 152;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 296;

enum RefreshMode { Display = 0 };

class EPD_2in66_DrawTarget : public Black1BitEPD {
  public:
    std::string GetDeviceName() const override { return "2.66inch e-paper"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }
    
    /// @brief Initialize the display
    void Init() {
        controller::EPD_2IN66_Init();
    }

    /// @brief Initialize the display
    void Init_partial() {
        controller::EPD_2IN66_Init_partial();
    }

    /// @brief Clear the display
    void Clear() {
        controller::EPD_2IN66_Clear();
    }

    /// @brief Put the display to sleep
    void Sleep() {
        controller::EPD_2IN66_Sleep();
    }

    /// @brief Display pixels in buffers to display
    void Display() {
        controller::EPD_2IN66_Display(packedBits);
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

    EPD_2in66_DrawTarget() : Black1BitEPD(GetWidth(), GetHeight()) {}
    ~EPD_2in66_DrawTarget() {}
};

} // namespace EPD_2in66

} // namespace devices

} // namespace epaperapi