/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 5.83inch e-paper b&c
 * Shortname: EPD_5in83bc
 * Generated On: 27 January 2025 @ 5:09 AM
 * Supported Color Channels: black,red
 * Type: RedBlack1BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "5.83inch e-paper b&c",
 *   "ScreenWidth": 600,
 *   "ScreenHeight": 448,
 *   "SupportedColorChannels": [
 *     "black",
 *     "red"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_5IN83BC_Init()"
 *     ],
 *     "Clear": [
 *       "EPD_5IN83BC_Clear()"
 *     ],
 *     "Display": [
 *       "EPD_5IN83BC_Display(const UBYTE *blackimage, const UBYTE *ryimage)"
 *     ],
 *     "Display_Base": [],
 *     "Display_Partial": [
 *       "EPD_5IN83BC_DisplayHalfScreen(const UBYTE *blackimage, const UBYTE *ryimage)"
 *     ],
 *     "Display_Fast": [],
 *     "Display_Misc": [],
 *     "Sleep": [
 *       "EPD_5IN83BC_Sleep()"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "The EPD_5IN83BC_Display and EPD_5IN83BC_DisplayHalfScreen functions suggest a dual-color display using
 * black and red/yellow channels, often seen on bicolor e-paper displays. The categories were assigned based on typical
 * function naming conventions.",
 *   "PaintRotation": 0,
 *   "BitmapFunction": "GUI_ReadBmp"
 * }
 */
 
#pragma once

#include "../EPD_Common.h"

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief 5.83inch e-paper b&c
namespace EPD_5in83bc {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_5in83bc.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 600;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 448;

enum RefreshMode { Display = 0, DisplayHalfScreen = 1 };

class EPD_5in83bc_DrawTarget : public RedBlack1BitEPD {
  public:
    std::string GetDeviceName() const override { return "5.83inch e-paper b&c"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }
    
    /// @brief Initialize the display
    void Init() {
        controller::EPD_5IN83BC_Init();
    }

    /// @brief Clear the display
    void Clear() {
        controller::EPD_5IN83BC_Clear();
    }

    /// @brief Put the display to sleep
    void Sleep() {
        controller::EPD_5IN83BC_Sleep();
    }

    /// @brief Display pixels in buffers to display
    void Display() {
        controller::EPD_5IN83BC_Display(packedBitsBlack, packedBitsRed);
    }

    /// @brief Display pixels in buffers to display
    void DisplayHalfScreen() {
        controller::EPD_5IN83BC_DisplayHalfScreen(packedBitsBlack, packedBitsRed);
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

        case RefreshMode::DisplayHalfScreen:
        DisplayHalfScreen();
        break;


        default:
            throw UnsupportedRefreshMode(mode, GetDeviceName());
        }
        
    }

    EPD_5in83bc_DrawTarget(bool initializeSPI = true) : RedBlack1BitEPD(GetWidth(), GetHeight(), initializeSPI) {}
    ~EPD_5in83bc_DrawTarget() {}
};

} // namespace EPD_5in83bc

} // namespace devices

} // namespace epaperapi