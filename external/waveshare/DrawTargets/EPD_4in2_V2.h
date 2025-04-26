/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 4.2inch e-paper V2 V1.0
 * Shortname: EPD_4in2_V2
 * Generated On: 26 April 2025 @ 5:06 PM
 * Supported Color Channels: black
 * Type: Black2BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "4.2inch e-paper V2 V1.0",
 *   "ScreenWidth": 400,
 *   "ScreenHeight": 300,
 *   "SupportedColorChannels": [
 *     "black"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_4IN2_V2_Init(void)",
 *       "EPD_4IN2_V2_Init_Fast(UBYTE Mode)",
 *       "EPD_4IN2_V2_Init_4Gray(void)"
 *     ],
 *     "Clear": [
 *       "EPD_4IN2_V2_Clear(void)"
 *     ],
 *     "Display": [
 *       "EPD_4IN2_V2_Display(UBYTE *Image)"
 *     ],
 *     "Display_Base": [],
 *     "Display_Partial": [
 *       "EPD_4IN2_V2_PartialDisplay(UBYTE *Image, UWORD x, UWORD y, UWORD w, UWORD l)"
 *     ],
 *     "Display_Fast": [
 *       "EPD_4IN2_V2_Display_Fast(UBYTE *Image)"
 *     ],
 *     "Display_Misc": [],
 *     "Sleep": [
 *       "EPD_4IN2_V2_Sleep(void)"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "The EPD_4IN2_V2_Display function uses a single image pointer, indicating support for 'black'. Functions
 * specifically mention 4Gray and fast modes, offering additional initialization and display functionality. No other
 * color channels like 'red' are explicitly mentioned.",
 *   "PaintScale": 4,
 *   "PaintRotation": 0,
 *   "BitmapFunction": "GUI_ReadBmp"
 * }
 */
 
#pragma once

#include "../EPD_Common.h"

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief 4.2inch e-paper V2 V1.0
namespace EPD_4in2_V2 {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_4in2_V2.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 400;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 300;

enum RefreshMode { EPD_4IN2_V2_Display = 0, EPD_4IN2_V2_Fast = 1 };

class EPD_4in2_V2_DrawTarget : public Black2BitEPD {
  public:
    std::string GetDeviceName() const override { return "4.2inch e-paper V2 V1.0"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }
    
    // The following functions were not created:

    //  ! EPD_4IN2_V2_Init_Fast(UBYTE Mode) was skipped because I'm not sure what arguments to pass in!
    //  ! EPD_4IN2_V2_PartialDisplay(UBYTE *Image, UWORD x, UWORD y, UWORD w, UWORD l) was skipped because I'm not sure what arguments to pass in!

    /// @brief Initialize the display
    void Init() {
        controller::EPD_4IN2_V2_Init();
    }

    /// @brief Initialize the display
    void Init_4Gray() {
        controller::EPD_4IN2_V2_Init_4Gray();
    }

    /// @brief Clear the display
    void Clear() {
        controller::EPD_4IN2_V2_Clear();
    }

    /// @brief Put the display to sleep
    void Sleep() {
        controller::EPD_4IN2_V2_Sleep();
    }

    /// @brief Display pixels in 2 bit buffer to display (4 shades of gray)
    void EPD_4IN2_V2_Display() {
        controller::EPD_4IN2_V2_Display(packedBits_2bit);
    }

    /// @brief Display pixels in 2 bit buffer to display (4 shades of gray)
    void EPD_4IN2_V2_Display_Fast() {
        controller::EPD_4IN2_V2_Display_Fast(packedBits_2bit);
    }

    /// @brief Refresh the display with current buffer
    /// @param mode How to refresh the display
    void Refresh(int mode) override {
        if (!IsOpen()) {
            throw RefreshingClosedDevice(GetDeviceName());
        }

        PreprocessBuffers();

        switch (static_cast<RefreshMode>(mode)) {
        case RefreshMode::EPD_4IN2_V2_Display:
        EPD_4IN2_V2_Display();
        break;

        case RefreshMode::EPD_4IN2_V2_Fast:
        EPD_4IN2_V2_Display_Fast();
        break;


        default:
            throw UnsupportedRefreshMode(mode, GetDeviceName());
        }
        
    }

    EPD_4in2_V2_DrawTarget(bool initializeSPI = true) : Black2BitEPD(GetWidth(), GetHeight(), initializeSPI) {}
    ~EPD_4in2_V2_DrawTarget() {}
};

} // namespace EPD_4in2_V2

} // namespace devices

} // namespace epaperapi