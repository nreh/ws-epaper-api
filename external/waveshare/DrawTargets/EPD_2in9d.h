/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 2.9inch e-paper d
 * Shortname: EPD_2in9d
 * Generated On: 27 January 2025 @ 2:59 AM
 * Supported Color Channels: black
 * Type: Black1BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "2.9inch e-paper d",
 *   "ScreenWidth": 128,
 *   "ScreenHeight": 296,
 *   "SupportedColorChannels": [
 *     "black"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_2IN9D_Init()"
 *     ],
 *     "Clear": [
 *       "EPD_2IN9D_Clear()"
 *     ],
 *     "Display": [
 *       "EPD_2IN9D_Display(UBYTE *Image)"
 *     ],
 *     "Display_Base": [],
 *     "Display_Partial": [
 *       "EPD_2IN9D_DisplayPart(UBYTE *Image)"
 *     ],
 *     "Display_Fast": [],
 *     "Display_Misc": [],
 *     "Sleep": [
 *       "EPD_2IN9D_Sleep()"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "No specific color channels are mentioned; 'black' is assumed from standard practices. The function
 * EPD_2IN9D_DisplayPart suggests partial updates. Categorization of functions was based on typical naming conventions
 * for e-paper displays.",
 *   "PaintRotation": 270,
 *   "BitmapFunction": "GUI_ReadBmp"
 * }
 */
 
#pragma once

#include "../EPD_Common.h"

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief 2.9inch e-paper d
namespace EPD_2in9d {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_2in9d.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 128;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 296;

enum RefreshMode { Display = 0, DisplayPart = 1 };

class EPD_2in9d_DrawTarget : public Black1BitEPD {
  public:
    std::string GetDeviceName() const override { return "2.9inch e-paper d"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }
    
    /// @brief Initialize the display
    void Init() {
        controller::EPD_2IN9D_Init();
    }

    /// @brief Clear the display
    void Clear() {
        controller::EPD_2IN9D_Clear();
    }

    /// @brief Put the display to sleep
    void Sleep() {
        controller::EPD_2IN9D_Sleep();
    }

    /// @brief Display pixels in buffers to display
    void Display() {
        controller::EPD_2IN9D_Display(packedBits);
    }

    /// @brief Display pixels in buffers to display
    void DisplayPart() {
        controller::EPD_2IN9D_DisplayPart(packedBits);
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

        case RefreshMode::DisplayPart:
        DisplayPart();
        break;


        default:
            throw UnsupportedRefreshMode(mode, GetDeviceName());
        }
        
    }

    EPD_2in9d_DrawTarget() : Black1BitEPD(GetWidth(), GetHeight()) {}
    ~EPD_2in9d_DrawTarget() {}
};

} // namespace EPD_2in9d

} // namespace devices

} // namespace epaperapi