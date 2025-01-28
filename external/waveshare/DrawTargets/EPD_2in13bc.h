/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 2.13inch e-paper b&c
 * Shortname: EPD_2in13bc
 * Generated On: 27 January 2025 @ 5:09 AM
 * Supported Color Channels: black,red
 * Type: RedBlack1BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "2.13inch e-paper b&c",
 *   "ScreenWidth": 104,
 *   "ScreenHeight": 212,
 *   "SupportedColorChannels": [
 *     "black",
 *     "red"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_2IN13BC_Init()"
 *     ],
 *     "Clear": [
 *       "EPD_2IN13BC_Clear()"
 *     ],
 *     "Display": [
 *       "EPD_2IN13BC_Display(const UBYTE *blackimage, const UBYTE *ryimage)"
 *     ],
 *     "Display_Base": [],
 *     "Display_Partial": [],
 *     "Display_Fast": [],
 *     "Display_Misc": [],
 *     "Sleep": [
 *       "EPD_2IN13BC_Sleep()"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "The EPD_2IN13BC_Display function suggests a dual-color channel display using black and red (or yellow)
 * channels. Function categorization was straightforward based on typical e-paper operations.",
 *   "PaintRotation": 270,
 *   "BitmapFunction": "GUI_ReadBmp"
 * }
 */
 
#pragma once

#include "../EPD_Common.h"

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief 2.13inch e-paper b&c
namespace EPD_2in13bc {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_2in13bc.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 104;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 212;

enum RefreshMode { Display = 0 };

class EPD_2in13bc_DrawTarget : public RedBlack1BitEPD {
  public:
    std::string GetDeviceName() const override { return "2.13inch e-paper b&c"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }
    
    /// @brief Initialize the display
    void Init() {
        controller::EPD_2IN13BC_Init();
    }

    /// @brief Clear the display
    void Clear() {
        controller::EPD_2IN13BC_Clear();
    }

    /// @brief Put the display to sleep
    void Sleep() {
        controller::EPD_2IN13BC_Sleep();
    }

    /// @brief Display pixels in buffers to display
    void Display() {
        controller::EPD_2IN13BC_Display(packedBitsBlack, packedBitsRed);
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

    EPD_2in13bc_DrawTarget(bool initializeSPI = true) : RedBlack1BitEPD(GetWidth(), GetHeight(), initializeSPI) {}
    ~EPD_2in13bc_DrawTarget() {}
};

} // namespace EPD_2in13bc

} // namespace devices

} // namespace epaperapi