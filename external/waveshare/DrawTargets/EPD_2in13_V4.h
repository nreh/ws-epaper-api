#pragma once

#include "../EPD_Common.h"

extern "C" {
#include <DEV_Config.h>
}

namespace epaperapi {

/// @brief Waveshare devices that you can draw to
namespace devices {

/// @brief 2.13 inch display (Version 4)
namespace EPD_2in13_V4 {

/// @brief Access the underlying EPD class provided by Waveshare. Can be used for more low level control.
namespace controller {
extern "C" {
#include "../epaper/e-Paper/EPD_2in13_V4.h"
}
} // namespace controller

/// @brief Width of device in pixels
const int DEVICE_WIDTH = EPD_2in13_V4_WIDTH;

/// @brief Amount of memory each row of pixels takes. This is roughly 8 times smaller than the device pixel width because we
/// can store 8 pixels in a single byte. Total bytes sent to the device is DEVICE_MEMORYWIDTH * DEVICE_HEIGHT
const int DEVICE_MEMORYWIDTH = DEVICE_WIDTH % 8 == 0 ? DEVICE_WIDTH / 8 : DEVICE_WIDTH / 8 + 1;

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = EPD_2in13_V4_HEIGHT;

class EPD_2in13_DrawTarget : public PhysicalEPD {
  private:
    GrayscaleBuffer _buffer;

    /// @brief Instead of 1 pixel per byte, the E-Paper display expects 8 pixels per byte
    uint8_t* packedBits = new uint8_t[DEVICE_MEMORYWIDTH * DEVICE_HEIGHT];

    /// @brief If true, pins have been deactived and SPI closed. You'll need to call InitializeSPI() again before using the
    /// display.
    bool HasClosed = false;

  public:
    /// @brief Initialize pins and SPI protocol. You shouldn't have to run this manually as this is run automatically when
    /// the DrawTarget is created.
    void InitializeSPI() {
        DEV_Module_Init(); // initialize pins and SPI protocol
    }

    /// @brief Initializes the E-Paper display
    void Init() { controller::EPD_2in13_V4_Init(); }

    void FastInit() { controller::EPD_2in13_V4_Init_Fast(); }

    /// @brief Clear the screen to white
    void Clear() override { controller::EPD_2in13_V4_Clear(); }

    /// @brief Clear the screen to black
    void ClearBlack() { controller::EPD_2in13_V4_Clear_Black(); }

    /// @brief Draw current buffer onto the display
    void DisplayBuffer() {
        epaperapi::utils::Pack1Bit(_buffer.blackChannel, packedBits, DEVICE_WIDTH, DEVICE_HEIGHT);
        controller::EPD_2in13_V4_Display(packedBits);
    }

    void DisplayBufferFast() {
        epaperapi::utils::Pack1Bit(_buffer.blackChannel, packedBits, DEVICE_WIDTH, DEVICE_HEIGHT);
        controller::EPD_2in13_V4_Display_Fast(packedBits);
    }

    /// @brief Draw the current buffer onto the display
    void DisplayBufferBase() {
        epaperapi::utils::Pack1Bit(_buffer.blackChannel, packedBits, DEVICE_WIDTH, DEVICE_HEIGHT);
        controller::EPD_2in13_V4_Display_Base(packedBits);
    }

    /// @brief Partially refresh the display with a new image
    void DisplayBufferPartial() {
        epaperapi::utils::Pack1Bit(_buffer.blackChannel, packedBits, DEVICE_WIDTH, DEVICE_HEIGHT);
        controller::EPD_2in13_V4_Display_Partial(packedBits);
    }

    /// @brief Put the device to sleep
    void Sleep() override { controller::EPD_2in13_V4_Sleep(); }

    /// @brief Shuts off power to the device, ends SPI protocol, and deallocates memory
    void Exit() {
        DEV_Module_Exit();
        HasClosed = true;
    }

    /// @brief Refresh the display with current buffer
    /// @param mode How to refresh the display
    void Refresh(RefreshMode mode) override {
        epaperapi::utils::PosterizeGrayscale(_buffer, 2);

        switch (mode) {
        case RefreshMode::Normal:
            DisplayBuffer();
            break;

        case RefreshMode::Fast:
            DisplayBufferFast();
            break;

        case RefreshMode::Partial:
            DisplayBufferPartial();
            break;

        default:
            throw UnsupportedRefreshMode(mode, "EPD_2in13_V4");
        }
    }

    EPD_2in13_DrawTarget() : _buffer(DEVICE_WIDTH, DEVICE_HEIGHT), PhysicalEPD(_buffer) {
        buffer.FillBuffer(255);
        InitializeSPI();
    }

    ~EPD_2in13_DrawTarget() {
        delete[] packedBits;
        if (!HasClosed) {
            Exit();
        }
    }
};

} // namespace EPD_2in13_V4

} // namespace devices

} // namespace epaperapi