#pragma once

#include <iostream>
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

    PhysicalEPDDrawTarget(AbstractBuffer& _buffer, bool initializeSPI) : AbstractDrawTarget(_buffer) {
        if (initializeSPI) {
            InitializeSPI();
        }
    }

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

    virtual AbstractBuffer& GetBuffer() = 0;

    virtual void Init() = 0;
    virtual void Sleep() = 0;

    /// @brief Get the width of the physical display in pixels
    virtual int GetWidth() const = 0;

    /// @brief Get the height of the physical display in pixels
    virtual int GetHeight() const = 0;

    /// @brief In pretty much all the displays, the Buffer will need to be preprocessed in some way before being able to be
    /// sent to the epaper display. For example, on some displays, the pixels may need to be packed so that each byte
    /// contains 8 pixels. This function should be run before any calls to the display functions.
    virtual void PreprocessBuffers() = 0;

    /// @brief Pretty much does the opposite of `PreprocessBuffers()`, writes internal packed bits representation to the
    /// target buffer.
    virtual void UnpackBuffers(AbstractBuffer& target) = 0;
};

// These Buffer holder classes are used to address an issue with BaseClasses (PhysicalEPDDrawTarget in this case) being
// initialized before the buffer that it will hold is initialized resulting in undefined widths and heights. By inheritting
// from these holder classes, the relevant class can instantiate the buffer FIRST and then pass it to
// thePhysicalEPDDrawTarget base class.

class GrayScaleBufferHolder {
  protected:
    GrayscaleBuffer _buffer;
    GrayScaleBufferHolder(uint16_t width, uint16_t height) : _buffer(width, height) {}
};

class RedBlackBufferHolder {
  protected:
    RedBlackBuffer _buffer;
    RedBlackBufferHolder(uint16_t width, uint16_t height) : _buffer(width, height) {}
};

class RGBBufferHolder {
  protected:
    RGBBuffer _buffer;
    RGBBufferHolder(uint16_t width, uint16_t height) : _buffer(width, height) {}
};

/// @brief Represents an E-Paper display that displays a single 1 bit black channel
class Black1BitEPD : private GrayScaleBufferHolder, public PhysicalEPDDrawTarget {
  protected:
    /// @brief Instead of 1 pixel per byte, the E-Paper display expects 8 pixels per byte
    uint8_t* packedBits;

    /// @brief Get the number of bytes each row of pixels takes up.
    int GetMemoryWidth(int width) const { return width % 8 == 0 ? width / 8 : width / 8 + 1; }

    Black1BitEPD(int width, int height, bool initializeSPI = true)
        : GrayScaleBufferHolder(width, height), PhysicalEPDDrawTarget(_buffer, initializeSPI) {
        packedBits = new uint8_t[GetMemoryWidth(width) * height];
        buffer.FillBuffer(255);
    }

    /// @brief In pretty much all the displays, the Buffer will need to be preprocessed in some way before being able to be
    /// sent to the epaper display. For example, on some displays, the pixels may need to be packed so that each byte
    /// contains 8 pixels. This function should be run before any calls to the display functions.
    void PreprocessBuffers() override { _buffer.ConvertTo1Bit(packedBits); }

    ~Black1BitEPD() { delete[] packedBits; }

  public:
    AbstractBuffer& GetBuffer() override { return _buffer; }

    void UnpackBuffers(AbstractBuffer& target) override {
        if (target.type() != BufferType::GrayscaleBuffer) {
            throw std::runtime_error(
                "Cannot unpack buffer for " + GetDeviceName() +
                " as the target buffer is incompatible (expected GrayscaleBuffer)"
            );
        }

        auto t = static_cast<GrayscaleBuffer&>(target).blackChannel;

        auto memWidth = GetMemoryWidth(GetWidth());
        for (int y = 0; y < GetHeight(); y++) {
            for (int x = 0; x < GetWidth(); x++) {
                int byte_index = (y * memWidth) + (x / 8);
                int bit_index = x % 8;
                uint8_t pixel = packedBits[byte_index] >> (7 - bit_index) & 0x1;
                t[y * GetWidth() + x] = pixel == 1 ? 0xFF : 0x00;
            }
        }
    }
};

/// @brief Represents an E-Paper display that displays a single 2 bit black channel with 4 shades of gray
class Black2BitEPD : private GrayScaleBufferHolder, public PhysicalEPDDrawTarget {
  protected:
    /// @brief Instead of 1 pixel per byte, the E-Paper display expects 8 pixels per byte
    uint8_t* packedBits_1bit;

    /// @brief Store pixel data but this time for 4 shades of gray (meaning 2 bits per pixel)
    uint8_t* packedBits_2bit;

    /// @brief Get the number of bytes each row of pixels takes up.
    int GetMemoryWidth(int width) const { return width % 8 == 0 ? width / 8 : width / 8 + 1; }

    /// @brief Get ther number of bytes each row of pixels takes up when stored as 4 shades of gray
    int GetGrayscaleMemoryWidth(int width) const { return width % 4 == 0 ? width / 4 : width / 4 + 1; }

    Black2BitEPD(int width, int height, bool initializeSPI = true)
        : GrayScaleBufferHolder(width, height), PhysicalEPDDrawTarget(_buffer, initializeSPI) {
        packedBits_1bit = new uint8_t[GetMemoryWidth(width) * height];
        packedBits_2bit = new uint8_t[GetGrayscaleMemoryWidth(width) * height];
        buffer.FillBuffer(255);
    }

    /// @brief In pretty much all the displays, the Buffer will need to be preprocessed in some way before being able to be
    /// sent to the epaper display. For example, on some displays, the pixels may need to be packed so that each byte
    /// contains 8 pixels. This function should be run before any calls to the display functions.
    void PreprocessBuffers() override {
        _buffer.ConvertTo1Bit(packedBits_1bit);
        _buffer.ConvertTo2Bit(packedBits_2bit);
    }

    ~Black2BitEPD() {
        delete[] packedBits_1bit;
        delete[] packedBits_2bit;
    }

  public:
    AbstractBuffer& GetBuffer() override { return _buffer; }

    void UnpackBuffers(AbstractBuffer& target) override {
        if (target.type() != BufferType::GrayscaleBuffer) {
            throw std::runtime_error(
                "Cannot unpack buffer for " + GetDeviceName() +
                " as the target buffer is incompatible (expected GrayscaleBuffer)"
            );
        }

        auto t = static_cast<GrayscaleBuffer&>(target).blackChannel;

        // unlike other displays we have two buffers, use the 2 bit one

        auto memWidth = GetGrayscaleMemoryWidth(GetWidth());
        for (int y = 0; y < GetHeight(); y++) {
            for (int x = 0; x < GetWidth(); x++) {
                int byte_index = (y * memWidth) + (x / 4);
                int bit_index = (x % 4) * 2;
                uint8_t pixel = packedBits_2bit[byte_index] >> (6 - bit_index) & 0b11;
                uint8_t val;

                if (pixel == 0b11) {
                    val = 0;
                } else if (pixel == 0b10) {
                    val = 64;
                } else if (pixel == 0b01) {
                    val = 128;
                } else if (pixel == 0b0) {
                    val = 255;
                }

                t[y * GetWidth() + x] = val;
            }
        }
    }
};

/// @brief Represents an E-Paper display that displays a two 1 bit channels: Red and Black
class RedBlack1BitEPD : private RedBlackBufferHolder, public PhysicalEPDDrawTarget {
  protected:
    uint8_t* packedBitsBlack;
    uint8_t* packedBitsRed;

    /// @brief Get the number of bytes each row of pixels takes up.
    int GetMemoryWidth(int width) const { return width % 8 == 0 ? width / 8 : width / 8 + 1; }

    RedBlack1BitEPD(int width, int height, bool initializeSPI = true)
        : RedBlackBufferHolder(width, height), PhysicalEPDDrawTarget(_buffer, initializeSPI) {
        packedBitsBlack = new uint8_t[GetMemoryWidth(width) * height];
        packedBitsRed = new uint8_t[GetMemoryWidth(width) * height];
        buffer.FillBuffer(255);
    }

    /// @brief In pretty much all the displays, the Buffer will need to be preprocessed in some way before being able to be
    /// sent to the epaper display. For example, on some displays, the pixels may need to be packed so that each byte
    /// contains 8 pixels. This function should be run before any calls to the display functions.
    void PreprocessBuffers() override { _buffer.ConvertTo1Bit(packedBitsBlack, packedBitsRed); }

    ~RedBlack1BitEPD() {
        delete[] packedBitsBlack;
        delete[] packedBitsRed;
    }

  public:
    AbstractBuffer& GetBuffer() override { return _buffer; }

    void UnpackBuffers(AbstractBuffer& target) override {
        if (target.type() != BufferType::RedBlackBuffer) {
            throw std::runtime_error(
                "Cannot unpack buffer for " + GetDeviceName() +
                " as the target buffer is incompatible (expected RedBlackBuffer)"
            );
        }

        auto t1 = static_cast<RedBlackBuffer&>(target).blackChannel;
        auto t2 = static_cast<RedBlackBuffer&>(target).redChannel;

        auto memWidth = GetMemoryWidth(GetWidth());
        for (int y = 0; y < GetHeight(); y++) {
            for (int x = 0; x < GetWidth(); x++) {
                int byte_index = (y * memWidth) + (x / 8);
                int bit_index = x % 8;
                uint8_t pixel = packedBitsBlack[byte_index] >> (7 - bit_index) & 0x1;
                t1[y * GetWidth() + x] = pixel == 1 ? 0xFF : 0x00;
            }
        }
        for (int y = 0; y < GetHeight(); y++) {
            for (int x = 0; x < GetWidth(); x++) {
                int byte_index = (y * memWidth) + (x / 8);
                int bit_index = x % 8;
                uint8_t pixel = packedBitsRed[byte_index] >> (7 - bit_index) & 0x1;
                t2[y * GetWidth() + x] = pixel == 1 ? 255 : 0;
            }
        }
    }
};

/// @brief Represents an E-Paper display that displays 2 bit pixels with red/yellow/black color channels
class Color2BitEPD : private RGBBufferHolder, public PhysicalEPDDrawTarget {
  protected:
    utils::SupportedPalette palette = utils::SupportedPalette::Make4Color();
    uint8_t* packedBits;

    /// @brief Get the number of bytes each row of pixels takes up.
    int GetMemoryWidth(int width) const { return width % 4 == 0 ? width / 4 : width / 4 + 1; }

    Color2BitEPD(int width, int height, bool initializeSPI = true)
        : RGBBufferHolder(width, height), PhysicalEPDDrawTarget(_buffer, initializeSPI) {
        packedBits = new uint8_t[GetMemoryWidth(width) * height];
        buffer.FillBuffer(255);
    }

    /// @brief In pretty much all the displays, the Buffer will need to be preprocessed in some way before being able to be
    /// sent to the epaper display. For example, on some displays, the pixels may need to be packed so that each byte
    /// contains 8 pixels. This function should be run before any calls to the display functions.
    void PreprocessBuffers() override { _buffer.ConvertTo4Color(packedBits, GetMemoryWidth(width), palette); }

    ~Color2BitEPD() { delete[] packedBits; }

  public:
    AbstractBuffer& GetBuffer() override { return _buffer; }

    void UnpackBuffers(AbstractBuffer& target) override {
        if (target.type() != BufferType::RGBBuffer) {
            throw std::runtime_error(
                "Cannot unpack buffer for " + GetDeviceName() + " as the target buffer is incompatible (expected RGBBuffer)"
            );
        }

        auto rchannel = static_cast<RGBBuffer&>(target).redChannel;
        auto gchannel = static_cast<RGBBuffer&>(target).greenChannel;
        auto bchannel = static_cast<RGBBuffer&>(target).blueChannel;

        // unlike other displays we have two buffers, use the 2 bit one

        auto memWidth = GetMemoryWidth(GetWidth());
        for (int y = 0; y < GetHeight(); y++) {
            for (int x = 0; x < GetWidth(); x++) {
                int byte_index = (y * memWidth) + (x / 4);
                int bit_index = (x % 4) * 2;
                uint8_t pixel = packedBits[byte_index] >> (6 - bit_index) & 0b11;
                uint8_t val;
                uint32_t n = y * GetWidth() + x;

                if (pixel == 0) { // black
                    rchannel[n] = 0;
                    gchannel[n] = 0;
                    bchannel[n] = 0;
                } else if (pixel == 1) { // white
                    rchannel[n] = 255;
                    gchannel[n] = 255;
                    bchannel[n] = 255;
                } else if (pixel == 2) { // yellow
                    rchannel[n] = 255;
                    gchannel[n] = 255;
                    bchannel[n] = 0;
                } else if (pixel == 3) { // red
                    rchannel[n] = 255;
                    gchannel[n] = 0;
                    bchannel[n] = 0;
                }
            }
        }
    }
};

class Color4BitEPD : public RGBBufferHolder, public PhysicalEPDDrawTarget {
  protected:
    uint8_t* packedBits;

    /// @brief Get the number of bytes each row of pixels takes up.
    int GetMemoryWidth(int width) const { return width % 2 == 0 ? width / 2 : width / 2 + 1; }

    Color4BitEPD(int width, int height, bool initializeSPI = true)
        : RGBBufferHolder(width, height), PhysicalEPDDrawTarget(_buffer, initializeSPI) {
        packedBits = new uint8_t[GetMemoryWidth(width) * height];
        buffer.FillBuffer(255);
    }

  protected:
    ~Color4BitEPD() { delete[] packedBits; }

  public:
    AbstractBuffer& GetBuffer() override { return _buffer; }
};

class _6Color4BitEPD : public Color4BitEPD {
    using Color4BitEPD::Color4BitEPD;

  protected:
    utils::SupportedPalette palette = utils::SupportedPalette::Make6Color();

    /// @brief In pretty much all the displays, the Buffer will need to be preprocessed in some way before being able to be
    /// sent to the epaper display. For example, on some displays, the pixels may need to be packed so that each byte
    /// contains 8 pixels. This function should be run before any calls to the display functions.
    void PreprocessBuffers() override { _buffer.ConvertTo6Color(packedBits, GetMemoryWidth(width), palette); }

    void UnpackBuffers(AbstractBuffer& target) override {
        if (target.type() != BufferType::RGBBuffer) {
            throw std::runtime_error(
                "Cannot unpack buffer for " + GetDeviceName() + " as the target buffer is incompatible (expected RGBBuffer)"
            );
        }

        auto rchannel = static_cast<RGBBuffer&>(target).redChannel;
        auto gchannel = static_cast<RGBBuffer&>(target).greenChannel;
        auto bchannel = static_cast<RGBBuffer&>(target).blueChannel;

        auto memWidth = GetMemoryWidth(GetWidth());
        for (int y = 0; y < GetHeight(); y++) {
            for (int x = 0; x < GetWidth(); x++) {
                int byte_index = (y * memWidth) + (x / 2);
                int bit_index = (x % 2) * 4;
                uint8_t pixel = packedBits[byte_index] >> (4 - bit_index) & 0x0F;
                uint8_t val;
                uint32_t n = y * GetWidth() + x;

                if (pixel == 0) { // black
                    rchannel[n] = 0;
                    gchannel[n] = 0;
                    bchannel[n] = 0;
                } else if (pixel == 1) { // white
                    rchannel[n] = 255;
                    gchannel[n] = 255;
                    bchannel[n] = 255;
                } else if (pixel == 2) { // yellow
                    rchannel[n] = 255;
                    gchannel[n] = 255;
                    bchannel[n] = 0;
                } else if (pixel == 3) { // red
                    rchannel[n] = 255;
                    gchannel[n] = 0;
                    bchannel[n] = 0;
                } else if (pixel == 4) { // blue
                    rchannel[n] = 0;
                    gchannel[n] = 0;
                    bchannel[n] = 255;
                } else if (pixel == 5) { // green
                    rchannel[n] = 0;
                    gchannel[n] = 255;
                    bchannel[n] = 0;
                }
            }
        }
    }
};

class _7Color4BitEPD : public Color4BitEPD {
    using Color4BitEPD::Color4BitEPD;

  protected:
    utils::SupportedPalette palette = utils::SupportedPalette::Make7Color();

    /// @brief In pretty much all the displays, the Buffer will need to be preprocessed in some way before being able to be
    /// sent to the epaper display. For example, on some displays, the pixels may need to be packed so that each byte
    /// contains 8 pixels. This function should be run before any calls to the display functions.
    void PreprocessBuffers() override { _buffer.ConvertTo7Color(packedBits, GetMemoryWidth(width), palette); }

    void UnpackBuffers(AbstractBuffer& target) override {
        if (target.type() != BufferType::RGBBuffer) {
            throw std::runtime_error(
                "Cannot unpack buffer for " + GetDeviceName() + " as the target buffer is incompatible (expected RGBBuffer)"
            );
        }

        auto rchannel = static_cast<RGBBuffer&>(target).redChannel;
        auto gchannel = static_cast<RGBBuffer&>(target).greenChannel;
        auto bchannel = static_cast<RGBBuffer&>(target).blueChannel;

        auto memWidth = GetMemoryWidth(GetWidth());
        for (int y = 0; y < GetHeight(); y++) {
            for (int x = 0; x < GetWidth(); x++) {
                int byte_index = (y * memWidth) + (x / 2);
                int bit_index = (x % 2) * 4;
                uint8_t pixel = packedBits[byte_index] >> (4 - bit_index) & 0x0F;
                uint8_t val;
                uint32_t n = y * GetWidth() + x;

                if (pixel == 0) { // black
                    rchannel[n] = 0;
                    gchannel[n] = 0;
                    bchannel[n] = 0;
                } else if (pixel == 1) { // white
                    rchannel[n] = 255;
                    gchannel[n] = 255;
                    bchannel[n] = 255;
                } else if (pixel == 2) { // green
                    rchannel[n] = 0;
                    gchannel[n] = 255;
                    bchannel[n] = 0;
                } else if (pixel == 3) { // blue
                    rchannel[n] = 0;
                    gchannel[n] = 0;
                    bchannel[n] = 255;
                } else if (pixel == 4) { // red
                    rchannel[n] = 255;
                    gchannel[n] = 0;
                    bchannel[n] = 0;
                } else if (pixel == 5) { // yellow
                    rchannel[n] = 255;
                    gchannel[n] = 255;
                    bchannel[n] = 0;
                } else if (pixel == 6) { // orange
                    rchannel[n] = 255;
                    gchannel[n] = 165;
                    bchannel[n] = 0;
                }
            }
        }
    }
};

} // namespace devices

} // namespace epaperapi