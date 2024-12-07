#pragma once

#include <memory>
#include <stdexcept>
#include <string>

#include "../include/wsepaperapi.h"

namespace epaperapi {

namespace devices {

/// @brief Access underlying bcm2835 hardware interface library
namespace interface {
extern "C" {
#include "DEV_Config.h"
}
} // namespace interface

/// @brief Raised when an epaper display is refreshed with an invalid RefreshMode. For example, not all displays support
/// Partial refreshes.
class UnsupportedRefreshMode : public std::runtime_error {
  public:
    explicit UnsupportedRefreshMode(const int refreshMode, const std::string deviceName)
        : std::runtime_error(
              "The device '" + deviceName + "' does not support this refresh mode (" + std::to_string(refreshMode) + ")"
          ) {}
};

/// @brief Raised when a closed epaper display is attempted to be refreshed. This generally happens when you call Refresh()
/// after calling Exit().
class RefreshingClosedDevice : public std::runtime_error {
  public:
    explicit RefreshingClosedDevice(const std::string deviceName)
        : std::runtime_error("Cannot refresh closed device '" + deviceName + "'. Call InitializeSPI() before refreshing") {}
};

/// @brief Represents a physical display that can be drawn to. All physical EPD devices inherit from this class.
/// Common logic between displays is implemented here.
class PhysicalEPDDrawTarget : public AbstractDrawTarget {
  protected:
    bool Open = false;
    bool AutoExit = true;

    PhysicalEPDDrawTarget(AbstractBuffer& _buffer) : AbstractDrawTarget(_buffer) { InitializeSPI(); }

  public:
    virtual std::string GetDeviceName() const = 0;

    /// @brief Whether or not the SPI connection / pins are set up. Calling `Exit()` will result in this returning false.
    /// @return
    bool IsOpen() const { return Open; }

    /// @brief Returns true if the Exit() function will be automatically called on this object's destruction.
    bool WillAutoExit() const { return AutoExit; }

    /// @brief Enable/Disable AutoExit which automatically calls the Exit() function on this object's destruction.
    /// @param value True to call Exit(), False to not.
    void SetAutoExit(bool value) { AutoExit = value; }

    /// @brief Initialize pins and SPI protocol. You shouldn't have to run this manually as this is run automatically when
    /// the class is initialized.
    void InitializeSPI() {
        interface::DEV_Module_Init();
        Open = true;
    }

    /// @brief Shuts off power to the device, ends SPI protocol, and deallocates memory
    void Exit() {
        interface::DEV_Module_Exit();
        Open = false;
    }

    ~PhysicalEPDDrawTarget() {
        if (IsOpen() && WillAutoExit()) {
            Exit();
        }
    }

    virtual void Init() = 0;
    virtual void Display() = 0;
    virtual void Sleep() = 0;

    /// @brief Get the width of the physical display in pixels
    virtual int GetWidth() const = 0;

    /// @brief Get the height of the physical display in pixels
    virtual int GetHeight() const = 0;

    /// @brief In pretty much all the displays, the Buffer will need to be preprocessed in some way before being able to be
    /// sent to the epaper display. For example, on some displays, the pixels may need to be packed so that each byte
    /// contains 8 pixels. This function should be run before any calls to the display functions.
    virtual void PreprocessBuffers() = 0;
};

/// @brief Represents an E-Paper display that displays a single 1 bit black channel
class Black1BitEPD : public PhysicalEPDDrawTarget {
  protected:
    GrayscaleBuffer _buffer;

    /// @brief Instead of 1 pixel per byte, the E-Paper display expects 8 pixels per byte
    uint8_t* packedBits;

    /// @brief Get the number of bytes each row of pixels takes up.
    int GetMemoryWidth(int width) const { return width % 8 == 0 ? width / 8 : width / 8 + 1; }

    Black1BitEPD(int width, int height) : _buffer(width, height), PhysicalEPDDrawTarget(_buffer) {
        packedBits = new uint8_t[GetMemoryWidth(width) * height];
        buffer.FillBuffer(255);
    }

    /// @brief In pretty much all the displays, the Buffer will need to be preprocessed in some way before being able to be
    /// sent to the epaper display. For example, on some displays, the pixels may need to be packed so that each byte
    /// contains 8 pixels. This function should be run before any calls to the display functions.
    void PreprocessBuffers() override {
        epaperapi::utils::PosterizeGrayscale(_buffer, 2);
        epaperapi::utils::Pack1Bit(_buffer.blackChannel, packedBits, GetWidth(), GetHeight());
    }

    ~Black1BitEPD() { delete[] packedBits; }
};

/// @brief Represents an E-Paper display that displays a two 1 bit channels: Red and Black
class RedBlack1BitEPD : public PhysicalEPDDrawTarget {
  protected:
    RedBlackBuffer _buffer;

    uint8_t* packedBitsBlack;
    uint8_t* packedBitsRed;

    /// @brief Get the number of bytes each row of pixels takes up.
    int GetMemoryWidth(int width) const { return width % 8 == 0 ? width / 8 : width / 8 + 1; }

    RedBlack1BitEPD(int width, int height) : _buffer(width, height), PhysicalEPDDrawTarget(_buffer) {
        packedBitsBlack = new uint8_t[GetMemoryWidth(width) * height];
        packedBitsRed = new uint8_t[GetMemoryWidth(width) * height];
        buffer.FillBuffer(255);
    }

    /// @brief In pretty much all the displays, the Buffer will need to be preprocessed in some way before being able to be
    /// sent to the epaper display. For example, on some displays, the pixels may need to be packed so that each byte
    /// contains 8 pixels. This function should be run before any calls to the display functions.
    void PreprocessBuffers() override {
        epaperapi::utils::Pack1Bit(_buffer.blackChannel, packedBitsBlack, GetWidth(), GetHeight());
        epaperapi::utils::Pack1Bit(_buffer.redChannel, packedBitsRed, GetWidth(), GetHeight());
    }

    ~RedBlack1BitEPD() {
        delete[] packedBitsBlack;
        delete[] packedBitsRed;
    }
};

/// @brief Represents an E-Paper display that displays 2 bit pixels with red/yellow/black color channels
class Color2BitEPD : public PhysicalEPDDrawTarget {
  protected:
    RGBBuffer _buffer;

    uint8_t* packedBits;

    /// @brief Get the number of bytes each row of pixels takes up.
    int GetMemoryWidth(int width) const { return width % 4 == 0 ? width / 4 : width / 4 + 1; }

    Color2BitEPD(int width, int height) : _buffer(width, height), PhysicalEPDDrawTarget(_buffer) {
        packedBits = new uint8_t[GetMemoryWidth(width) * height];
        buffer.FillBuffer(255);
    }

    /// @brief In pretty much all the displays, the Buffer will need to be preprocessed in some way before being able to be
    /// sent to the epaper display. For example, on some displays, the pixels may need to be packed so that each byte
    /// contains 8 pixels. This function should be run before any calls to the display functions.
    void PreprocessBuffers() override { _buffer.ConvertTo4Color(packedBits); }

    ~Color2BitEPD() { delete[] packedBits; }
};

class Color4BitEPD : public PhysicalEPDDrawTarget {
  protected:
    RGBBuffer _buffer;

    uint8_t* packedBits;

    /// @brief Get the number of bytes each row of pixels takes up.
    int GetMemoryWidth(int width) const { return width % 2 == 0 ? width / 2 : width / 2 + 1; }

    Color4BitEPD(int width, int height) : _buffer(width, height), PhysicalEPDDrawTarget(_buffer) {
        packedBits = new uint8_t[GetMemoryWidth(width) * height];
        buffer.FillBuffer(255);
    }

  public:
    /// @brief When true, the RGB conversion to 4 bit color will use different logic which may result in better (or worse)
    /// color conversion. Defaults to true, set to false if experiences color artifacts or problems.
    bool use6ColorVariant2 = true;

  protected:
    /// @brief In pretty much all the displays, the Buffer will need to be preprocessed in some way before being able to be
    /// sent to the epaper display. For example, on some displays, the pixels may need to be packed so that each byte
    /// contains 8 pixels. This function should be run before any calls to the display functions.
    void PreprocessBuffers() override { _buffer.ConvertTo6Color(packedBits); }

    ~Color4BitEPD() { delete[] packedBits; }
};

} // namespace devices

} // namespace epaperapi