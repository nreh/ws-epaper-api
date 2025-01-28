/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 4.01inch e-paper
 * Shortname: EPD_4in01f
 * Generated On: 27 January 2025 @ 5:09 AM
 * Supported Color Channels: black,red,green,blue,yellow,orange
 * Type: _7Color4BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "4.01inch e-paper",
 *   "ScreenWidth": 640,
 *   "ScreenHeight": 400,
 *   "SupportedColorChannels": [
 *     "black",
 *     "red",
 *     "green",
 *     "blue",
 *     "yellow",
 *     "orange"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_Init(void)",
 *       "EPD_4IN01F_Init(void)"
 *     ],
 *     "Clear": [
 *       "EPD_4IN01F_Clear(UBYTE color)",
 *       "EPD_4IN01F_ReClear(void)"
 *     ],
 *     "Display": [
 *       "EPD_4IN01F_Display(const UBYTE *image)"
 *     ],
 *     "Display_Base": [],
 *     "Display_Partial": [
 *       "EPD_4IN01F_Display_part(const UBYTE *image, UWORD xstart, UWORD ystart, UWORD image_width, UWORD image_heigh)"
 *     ],
 *     "Display_Fast": [],
 *     "Display_Misc": [
 *       "EPD_4IN01F_Show7Block(void)"
 *     ],
 *     "Sleep": [
 *       "EPD_4IN01F_Sleep(void)"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "The SupportedColorChannels include black, red, green, blue, yellow, and orange as defined by the color
 * index. WHITE and CLEAN are ignored, following the guideline to treat them as part of the 'black' channel. Multiple
 * initialization functions are provided; 'EPD_Init' seems to be a generic initialization function.",
 *   "PaintScale": 7,
 *   "PaintRotation": 0,
 *   "BitmapFunction": "GUI_ReadBmp_RGB_7Color"
 * }
 */
 
#pragma once

#include "../EPD_Common.h"

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief 4.01inch e-paper
namespace EPD_4in01f {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_4in01f.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 640;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 400;

enum RefreshMode { Display = 0, Display = 1 };

class EPD_4in01f_DrawTarget : public _7Color4BitEPD {
  public:
    std::string GetDeviceName() const override { return "4.01inch e-paper"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }
    
    // The following functions were not created:

    //  ! EPD_4IN01F_Clear(UBYTE color) was skipped because I'm not sure what arguments to pass in!
    //  ! EPD_4IN01F_Display_part(const UBYTE *image, UWORD xstart, UWORD ystart, UWORD image_width, UWORD image_heigh) was skipped because I'm not sure what arguments to pass in!

    /// @brief Initialize the display
    void Init() {
        controller::EPD_Init();
    }

    /// @brief Initialize the display
    void Init() {
        controller::EPD_4IN01F_Init();
    }

    /// @brief Clear the display
    void Clear() {
        controller::EPD_4IN01F_ReClear();
    }

    /// @brief Put the display to sleep
    void Sleep() {
        controller::EPD_4IN01F_Sleep();
    }

    /// @brief Display pixels in buffers to display
    void Display() {
        controller::EPD_4IN01F_Show7Block();
    }

    /// @brief Display pixels in buffers to display
    void Display() {
        controller::EPD_4IN01F_Display(packedBits);
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

        case RefreshMode::Display:
        Display();
        break;


        default:
            throw UnsupportedRefreshMode(mode, GetDeviceName());
        }
        
    }

    EPD_4in01f_DrawTarget(bool initializeSPI = true) : _7Color4BitEPD(GetWidth(), GetHeight(), initializeSPI) {}
    ~EPD_4in01f_DrawTarget() {}
};

} // namespace EPD_4in01f

} // namespace devices

} // namespace epaperapi