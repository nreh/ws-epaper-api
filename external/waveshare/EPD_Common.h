#pragma once

#include <stdexcept>
#include <string>

namespace epaperapi {

enum class RefreshMode { Normal, Fast, Partial };

namespace devices {

/// @brief Raised when an epaper display is refreshed with an invalid RefreshMode. For example, not all displays support
/// Partial refreshes.
class UnsupportedRefreshMode : public std::runtime_error {
  public:
    explicit UnsupportedRefreshMode(const RefreshMode refreshMode, const std::string deviceName)
        : std::runtime_error("The device '" + deviceName + "' deos not support this refresh mode") {}
};

} // namespace devices

} // namespace epaperapi