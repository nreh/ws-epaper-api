/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 4.2inch e-paper b&c
 * Shortname: EPD_4in2bc
 * Generated On: 27 January 2025 @ 2:59 AM
 * Supported Color Channels: red,black
 * Type: RedBlack1BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "4.2inch e-paper b&c",
 *   "ScreenWidth": 400,
 *   "ScreenHeight": 300,
 *   "SupportedColorChannels": [
 *     "red",
 *     "black"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_4IN2BC_Init()"
 *     ],
 *     "Clear": [
 *       "EPD_4IN2BC_Clear()"
 *     ],
 *     "Display": [
 *       "EPD_4IN2BC_Display(const UBYTE *blackimage, const UBYTE *ryimage)"
 *     ],
 *     "Display_Base": [],
 *     "Display_Partial": [],
 *     "Display_Fast": [],
 *     "Display_Misc": [],
 *     "Sleep": [
 *       "EPD_4IN2BC_Sleep()"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "The display function takes two image parameters, suggesting 'red' and 'black' channels. Function
 * categorization is straightforward based on names.",
 *   "PaintRotation": 180,
 *   "BitmapFunction": "GUI_ReadBmp"
 * }
 */
 
#pragma once

#include "../EPD_Common.h"

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief 4.2inch e-paper b&c
namespace EPD_4in2bc {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_4in2bc.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 400;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 300;

enum RefreshMode { Display = 0 };

class EPD_4in2bc_DrawTarget : public RedBlack1BitEPD {
  public:
    std::string GetDeviceName() const override { return "4.2inch e-paper b&c"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }
    
    /// @brief Initialize the display
    void Init() {
        controller::EPD_4IN2BC_Init();
    }

    /// @brief Clear the display
    void Clear() {
        controller::EPD_4IN2BC_Clear();
    }

    /// @brief Put the display to sleep
    void Sleep() {
        controller::EPD_4IN2BC_Sleep();
    }

    /// @brief Display pixels in buffers to display
    void Display() {
        controller::EPD_4IN2BC_Display(packedBitsBlack, packedBitsRed);
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

    EPD_4in2bc_DrawTarget() : RedBlack1BitEPD(GetWidth(), GetHeight()) {}
    ~EPD_4in2bc_DrawTarget() {}
};

} // namespace EPD_4in2bc

} // namespace devices

} // namespace epaperapi