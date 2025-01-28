/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 2.13inch e-paper V2 V3.0
 * Shortname: EPD_2in13_V2
 * Generated On: 27 January 2025 @ 5:09 AM
 * Supported Color Channels: black
 * Type: Black1BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "2.13inch e-paper V2 V3.0",
 *   "ScreenWidth": 122,
 *   "ScreenHeight": 250,
 *   "SupportedColorChannels": [
 *     "black"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_2IN13_V2_Init(UBYTE Mode)"
 *     ],
 *     "Clear": [
 *       "EPD_2IN13_V2_Clear(void)"
 *     ],
 *     "Display": [
 *       "EPD_2IN13_V2_Display(UBYTE *Image)"
 *     ],
 *     "Display_Base": [
 *       "EPD_2IN13_V2_DisplayPartBaseImage(UBYTE *Image)"
 *     ],
 *     "Display_Partial": [
 *       "EPD_2IN13_V2_DisplayPart(UBYTE *Image)"
 *     ],
 *     "Display_Fast": [],
 *     "Display_Misc": [],
 *     "Sleep": [
 *       "EPD_2IN13_V2_Sleep(void)"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "The EPD_2IN13_V2_Display function uses a single image pointer, indicating support for 'black'. The
 * categorization of functions such as EPD_2IN13_V2_DisplayPart and EPD_2IN13_V2_DisplayPartBaseImage are assumed based
 * on their function names. The Display should refer to the default display function, while DisplayPartBaseImage is
 * categorized under Display_Base.",
 *   "PaintRotation": 270,
 *   "BitmapFunction": "GUI_ReadBmp"
 * }
 */
 
#pragma once

#include "../EPD_Common.h"

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief 2.13inch e-paper V2 V3.0
namespace EPD_2in13_V2 {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_2in13_V2.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 122;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 250;

enum RefreshMode { Display = 0, DisplayPart = 1, DisplayPartBaseImage = 2 };

class EPD_2in13_V2_DrawTarget : public Black1BitEPD {
  public:
    std::string GetDeviceName() const override { return "2.13inch e-paper V2 V3.0"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }
    
    // The following functions were not created:

    //  ! EPD_2IN13_V2_Init(UBYTE Mode) was skipped because I'm not sure what arguments to pass in!

    /// @brief Clear the display
    void Clear() {
        controller::EPD_2IN13_V2_Clear();
    }

    /// @brief Put the display to sleep
    void Sleep() {
        controller::EPD_2IN13_V2_Sleep();
    }

    /// @brief Display pixels in buffers to display
    void Display() {
        controller::EPD_2IN13_V2_Display(packedBits);
    }

    /// @brief Display pixels in buffers to display
    void DisplayPart() {
        controller::EPD_2IN13_V2_DisplayPart(packedBits);
    }

    /// @brief Display pixels in buffers to display
    void DisplayPartBaseImage() {
        controller::EPD_2IN13_V2_DisplayPartBaseImage(packedBits);
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

    EPD_2in13_V2_DrawTarget(bool initializeSPI = true) : Black1BitEPD(GetWidth(), GetHeight(), initializeSPI) {}
    ~EPD_2in13_V2_DrawTarget() {}
};

} // namespace EPD_2in13_V2

} // namespace devices

} // namespace epaperapi