/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 2.15inch e-paper b
 * Shortname: EPD_2in15b
 * Generated On: 27 January 2025 @ 5:09 AM
 * Supported Color Channels: black,red
 * Type: RedBlack1BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "2.15inch e-paper b",
 *   "ScreenWidth": 160,
 *   "ScreenHeight": 296,
 *   "SupportedColorChannels": [
 *     "black",
 *     "red"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_2IN15B_Init(void)"
 *     ],
 *     "Clear": [
 *       "EPD_2IN15B_Clear(void)",
 *       "EPD_2IN15B_Clear_Black(void)",
 *       "EPD_2IN15B_Clear_Red(void)"
 *     ],
 *     "Display": [
 *       "EPD_2IN15B_Display(UBYTE *ImageBlack, UBYTE*ImageRed)"
 *     ],
 *     "Display_Base": [],
 *     "Display_Partial": [],
 *     "Display_Fast": [],
 *     "Display_Misc": [],
 *     "Sleep": [
 *       "EPD_2IN15B_Sleep(void)"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "The SupportedColorChannels include 'black' and 'red' due to the presence of EPD_2IN15B_Display function
 * which accepts black and red image inputs. The only clearing options are for overall, black, and red.",
 *   "PaintRotation": 270,
 *   "BitmapFunction": "GUI_ReadBmp"
 * }
 */
 
#pragma once

#include "../EPD_Common.h"

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief 2.15inch e-paper b
namespace EPD_2in15b {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_2in15b.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 160;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 296;

enum RefreshMode { Display = 0 };

class EPD_2in15b_DrawTarget : public RedBlack1BitEPD {
  public:
    std::string GetDeviceName() const override { return "2.15inch e-paper b"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }
    
    /// @brief Initialize the display
    void Init() {
        controller::EPD_2IN15B_Init();
    }

    /// @brief Clear the display
    void Clear() {
        controller::EPD_2IN15B_Clear();
    }

    /// @brief Clear the display
    void Clear_Red() {
        controller::EPD_2IN15B_Clear_Red();
    }

    /// @brief Clear the display
    void Clear_Black() {
        controller::EPD_2IN15B_Clear_Black();
    }

    /// @brief Put the display to sleep
    void Sleep() {
        controller::EPD_2IN15B_Sleep();
    }

    /// @brief Display pixels in buffers to display
    void Display() {
        controller::EPD_2IN15B_Display(packedBitsBlack, packedBitsRed);
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

    EPD_2in15b_DrawTarget(bool initializeSPI = true) : RedBlack1BitEPD(GetWidth(), GetHeight(), initializeSPI) {}
    ~EPD_2in15b_DrawTarget() {}
};

} // namespace EPD_2in15b

} // namespace devices

} // namespace epaperapi