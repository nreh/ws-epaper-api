/**
 * This file was automatically generated using Generate.py in scripts/capabilitiesparser/Generate.py.
 * See the README.md in scripts/capabilitiesparser for more details.
 *
 * Display: 3.7inch e-paper
 * Shortname: EPD_3in7
 * Generated On: 26 April 2025 @ 5:41 PM
 * Supported Color Channels: black
 * Type: Black2BitEPD
 *
 * The following JSON data was used:
 * {
 *   "FullName": "3.7inch e-paper",
 *   "ScreenWidth": 280,
 *   "ScreenHeight": 480,
 *   "SupportedColorChannels": [
 *     "black"
 *   ],
 *   "Functions": {
 *     "Initialize": [
 *       "EPD_3IN7_4Gray_Init(void)",
 *       "EPD_3IN7_1Gray_Init(void)"
 *     ],
 *     "Clear": [
 *       "EPD_3IN7_4Gray_Clear(void)",
 *       "EPD_3IN7_1Gray_Clear(void)"
 *     ],
 *     "Display": [
 *       "EPD_3IN7_4Gray_Display(const UBYTE *Image)",
 *       "EPD_3IN7_1Gray_Display(const UBYTE *Image)"
 *     ],
 *     "Display_Base": [],
 *     "Display_Partial": [
 *       "EPD_3IN7_1Gray_Display_Part(const UBYTE *Image, UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend)"
 *     ],
 *     "Display_Fast": [],
 *     "Display_Misc": [
 *       "EPD_3IN7_1Gray_Display_Dithered(const UBYTE *Image, int Ditherer)"
 *     ],
 *     "Sleep": [
 *       "EPD_3IN7_Sleep(void)"
 *     ],
 *     "Misc": []
 *   },
 *   "Notes": "The SupportedColorChannels is set to 'black' due to the presence of 4GRAY functions which suggest support
 * for gray shades, interpreted under the 'black' channel according to the rules. Functions like
 * EPD_3IN7_1Gray_Display_Dithered suggest complex gray rendering but don't add additional colors beyond what's
 * covered.",
 *   "PaintScale": 4,
 *   "PaintRotation": 270,
 *   "BitmapFunction": "GUI_ReadBmp"
 * }
 */

#pragma once

#include "../EPD_Common.h"

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief 3.7inch e-paper
namespace EPD_3in7 {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_3in7.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = 280;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = 480;

enum RefreshMode { Display = 0, EPD_3IN7_4Gray_Display = 1 };

class EPD_3in7_DrawTarget : public Black2BitEPD {
  public:
    std::string GetDeviceName() const override { return "3.7inch e-paper"; }
    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }

    // The following functions were not created:

    //  ! EPD_3IN7_1Gray_Display_Part(const UBYTE *Image, UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend) was skipped
    //  because I'm not sure what arguments to pass in! ! EPD_3IN7_1Gray_Display_Dithered(const UBYTE *Image, int Ditherer)
    //  was skipped because I'm not sure what arguments to pass in!

    /// @brief Initialize the display
    void Init() { controller::EPD_3IN7_4Gray_Init(); }

    /// @brief Initialize the display
    void Init2() { controller::EPD_3IN7_1Gray_Init(); }

    /// @brief Clear the display
    void Clear() { controller::EPD_3IN7_4Gray_Clear(); }

    /// @brief Clear the display
    void Clear2() { controller::EPD_3IN7_1Gray_Clear(); }

    /// @brief Put the display to sleep
    void Sleep() { controller::EPD_3IN7_Sleep(); }

    /// @brief Display pixels in 1 bit buffer to display
    void Display() { controller::EPD_3IN7_1Gray_Display(packedBits_1bit); }

    /// @brief Display pixels in 2 bit buffer to display (4 shades of gray)
    void EPD_3IN7_4Gray_Display() { controller::EPD_3IN7_4Gray_Display(packedBits_2bit); }

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

        case RefreshMode::EPD_3IN7_4Gray_Display:
            EPD_3IN7_4Gray_Display();
            break;

        default:
            throw UnsupportedRefreshMode(mode, GetDeviceName());
        }
    }

    EPD_3in7_DrawTarget(bool initializeSPI = true) : Black2BitEPD(GetWidth(), GetHeight(), initializeSPI) {}
    ~EPD_3in7_DrawTarget() {}
};

} // namespace EPD_3in7

} // namespace devices

} // namespace epaperapi