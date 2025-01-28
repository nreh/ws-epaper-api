/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 1.54inch e-paper V2
 * Shortname: EPD_1in54_V2
 * Generated On: 27 January 2025 @ 5:09 AM
 * Supported Color Channels: black
 * Type: Black1BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "1.54inch e-paper V2",
 *   "ScreenWidth": 200,
 *   "ScreenHeight": 200,
 *   "SupportedColorChannels": [
 *     "black"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_1IN54_V2_Init()",
 *       "EPD_1IN54_V2_Init_Partial()"
 *     ],
 *     "Clear": [
 *       "EPD_1IN54_V2_Clear()"
 *     ],
 *     "Display": [
 *       "EPD_1IN54_V2_Display(UBYTE *Image)"
 *     ],
 *     "Display_Base": [
 *       "EPD_1IN54_V2_DisplayPartBaseImage(UBYTE *Image)"
 *     ],
 *     "Display_Partial": [
 *       "EPD_1IN54_V2_DisplayPart(UBYTE *Image)"
 *     ],
 *     "Display_Fast": [],
 *     "Display_Misc": [],
 *     "Sleep": [
 *       "EPD_1IN54_V2_Sleep()"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "The display primarily supports the black color channel, with no indication of additional colors. The
 * various display functions suggest support for full and partial image updates, with DisplayPartBaseImage indicating a
 * base image setup possibly for partial updates. The presence of partial initialization and display support aligns with
 * these observations.",
 *   "PaintRotation": 270,
 *   "BitmapFunction": "GUI_ReadBmp"
 * }
 */
 
#pragma once

#include "../EPD_Common.h"

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief 1.54inch e-paper V2
namespace EPD_1in54_V2 {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_1in54_V2.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 200;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 200;

enum RefreshMode { Display = 0, DisplayPart = 1, DisplayPartBaseImage = 2 };

class EPD_1in54_V2_DrawTarget : public Black1BitEPD {
  public:
    std::string GetDeviceName() const override { return "1.54inch e-paper V2"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }
    
    /// @brief Initialize the display
    void Init() {
        controller::EPD_1IN54_V2_Init();
    }

    /// @brief Initialize the display
    void Init_Partial() {
        controller::EPD_1IN54_V2_Init_Partial();
    }

    /// @brief Clear the display
    void Clear() {
        controller::EPD_1IN54_V2_Clear();
    }

    /// @brief Put the display to sleep
    void Sleep() {
        controller::EPD_1IN54_V2_Sleep();
    }

    /// @brief Display pixels in buffers to display
    void Display() {
        controller::EPD_1IN54_V2_Display(packedBits);
    }

    /// @brief Display pixels in buffers to display
    void DisplayPart() {
        controller::EPD_1IN54_V2_DisplayPart(packedBits);
    }

    /// @brief Display pixels in buffers to display
    void DisplayPartBaseImage() {
        controller::EPD_1IN54_V2_DisplayPartBaseImage(packedBits);
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

        case RefreshMode::DisplayPartBaseImage:
        DisplayPartBaseImage();
        break;


        default:
            throw UnsupportedRefreshMode(mode, GetDeviceName());
        }
        
    }

    EPD_1in54_V2_DrawTarget(bool initializeSPI = true) : Black1BitEPD(GetWidth(), GetHeight(), initializeSPI) {}
    ~EPD_1in54_V2_DrawTarget() {}
};

} // namespace EPD_1in54_V2

} // namespace devices

} // namespace epaperapi