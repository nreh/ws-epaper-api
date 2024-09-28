#pragma once

#include <wsepaperapi.h>

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief 2.13 inch display (Version 4)
namespace EPD_2in13_V4 {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
#include "../epaper/e-Paper/EPD_2in13_V4.h"
}

/// @brief Width of device in pixels
const int DEVICE_WIDTH = EPD_2in13_V4_WIDTH;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = EPD_2in13_V4_HEIGHT;

class EPD_2in13_DrawTarget : public AbstractDrawTarget {
    /// @brief Initializes the E-Paper display
    void Init() {
        controller::DEV_Module_Init(); // initialize pins and SPI protocol
        controller::EPD_2in13_V4_Init();
    }

    void FastInit() { controller::EPD_2in13_V4_Init_Fast(); }

    /// @brief Clear the screen to white
    void Clear() { controller::EPD_2in13_V4_Clear(); }

    /// @brief Clear the screen to black
    void ClearBlack() { controller::EPD_2in13_V4_Clear_Black(); }

    /// @brief Draw current buffer onto the display
    void DisplayBuffer() { controller::EPD_2in13_V4_Display(((GrayscaleBuffer&)buffer).blackChannel); }

    void DisplayBufferFast() { controller::EPD_2in13_V4_Display_Fast(((GrayscaleBuffer&)buffer).blackChannel); }

    /// @brief Draw the current buffer onto the display
    void DisplayBufferBase() { controller::EPD_2in13_V4_Display_Base(((GrayscaleBuffer&)buffer).blackChannel); }

    /// @brief Partially refresh the display with a new image
    void DisplayBufferPartial() { controller::EPD_2in13_V4_Display_Partial(((GrayscaleBuffer&)buffer).blackChannel); }

    /// @brief Put the device to sleep
    void Sleep() { controller::EPD_2in13_V4_Sleep(); }

    /// @brief Shuts off power to the device, ends SPI protocol, and deallocates memory
    void Exit() { controller::DEV_Module_Exit(); }
};

} // namespace EPD_2in13_V4

} // namespace devices

} // namespace epaperapi