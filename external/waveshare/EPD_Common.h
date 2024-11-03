#pragma once

#include <bufferutils.h>
#include <memory>
#include <stdexcept>
#include <string>
#include <wsepaperapi.h>

#include "DEV_Config.h"

namespace epaperapi {

/// @brief Indicates how the display should be refreshed. When in doubt, use Normal.
enum class RefreshMode { Normal, Fast, Partial };

namespace devices {

/// @brief Raised when an epaper display is refreshed with an invalid RefreshMode. For example, not all displays support
/// Partial refreshes.
class UnsupportedRefreshMode : public std::runtime_error {
  public:
    explicit UnsupportedRefreshMode(const RefreshMode refreshMode, const std::string deviceName)
        : std::runtime_error("The device '" + deviceName + "' deos not support this refresh mode") {}
};

/// @brief All physical EPD devices inherit from this abstract class. Common logic between displays is implemented here.
class PhysicalEPD : public AbstractDrawTarget {
  protected:
    bool Open = false;

  public:
    /// @brief Whether or not the SPI connection / pins are set up. Calling `Exit()` will result in this returning false.
    /// @return
    bool IsOpen() { return Open; }

    /// @brief Initialize pins and SPI protocol. You shouldn't have to run this manually as this is run automatically when
    /// the class is initialized.
    void InitializeSPI() {
        DEV_Module_Init();
        Open = true;
    }

    /// @brief Shuts off power to the device, ends SPI protocol, and deallocates memory
    void Exit() {
        DEV_Module_Exit();
        Open = false;
    }
};

} // namespace devices

} // namespace epaperapi