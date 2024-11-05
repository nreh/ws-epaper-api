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

/// @brief Height of device in pixels
const int DEVICE_HEIGHT = EPD_2in13_V4_HEIGHT;

enum RefreshMode { Normal = 0, Fast = 1, Partial = 2, Base = 3 };

class EPD_2in13_DrawTarget : public Black1BitEPD {
  public:
    std::string GetDeviceName() const override { return "EPD_2in13_V4"; }

    int GetWidth() const override { return DEVICE_WIDTH; }
    int GetHeight() const override { return DEVICE_HEIGHT; }

    /// @brief Initializes the E-Paper display
    void Init() override { controller::EPD_2in13_V4_Init(); }

    void FastInit() { controller::EPD_2in13_V4_Init_Fast(); }

    /// @brief Clear the screen to white
    void Clear() override { controller::EPD_2in13_V4_Clear(); }

    /// @brief Clear the screen to black
    void ClearBlack() { controller::EPD_2in13_V4_Clear_Black(); }

    /// @brief Draw current buffer onto the display
    void Display() { controller::EPD_2in13_V4_Display(packedBits); }

    void DisplayFast() { controller::EPD_2in13_V4_Display_Fast(packedBits); }

    /// @brief Draw the current buffer onto the display
    void DisplayBase() { controller::EPD_2in13_V4_Display_Base(packedBits); }

    /// @brief Partially refresh the display with a new image
    void DisplayPartial() { controller::EPD_2in13_V4_Display_Partial(packedBits); }

    /// @brief Put the device to sleep
    void Sleep() override { controller::EPD_2in13_V4_Sleep(); }

    /// @brief Refresh the display with current buffer
    /// @param mode How to refresh the display
    void Refresh(int mode) override {
        if (!IsOpen()) {
            throw RefreshingClosedDevice(GetDeviceName());
        }

        PreprocessBuffers();

        switch (static_cast<RefreshMode>(mode)) {
        case RefreshMode::Normal:
            Display();
            break;

        case RefreshMode::Fast:
            DisplayFast();
            break;

        case RefreshMode::Partial:
            DisplayPartial();
            break;

        case RefreshMode::Base:
            DisplayBase();
            break;

        default:
            throw UnsupportedRefreshMode(mode, GetDeviceName());
        }
    }

    EPD_2in13_DrawTarget() : Black1BitEPD(GetWidth(), GetHeight()) {}
    ~EPD_2in13_DrawTarget() {}
};

} // namespace EPD_2in13_V4

} // namespace devices

} // namespace epaperapi