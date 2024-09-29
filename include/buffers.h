#pragma once

#include <stdexcept>
#include <stdint.h>
#include <string>

namespace epaperapi {

enum class BufferType { AbstractBuffer, RGBBuffer, RedBlackBuffer, GrayscaleBuffer };
static const char* BufferTypeStrings[] = {"AbstractBuffer", "RGBBuffer", "RedBlackBuffer", "GrayscaleBuffer"};

/**
 * @brief A block of memory representing a rectangle of pixels.
 *
 * There are different types of buffers depending on the
 * physical capabilities of the device you're trying to draw on. For example, an e-paper display with only grayscale has no
 * need for an RGB buffer - that would be a waste of 2/3 of the bytes we'd allocate.
 *
 * For that reason, each use-case (grayscale, 2-color, RGB) has a different implementation of the Abstract buffer with
 * different capabilities and limitations for each.
 */
class AbstractBuffer {
  public:
    uint16_t width;
    uint16_t height;
    float* alphaChannel;

    AbstractBuffer(uint16_t _width, uint16_t _height);
    ~AbstractBuffer();
    virtual void Write(const AbstractBuffer& newValues, uint16_t xpos, uint16_t ypos) = 0;
    virtual BufferType type() const { return BufferType::AbstractBuffer; }

    /// @brief Get Buffer type as a string
    std::string TypeAsString() const { return std::string(BufferTypeStrings[static_cast<int>(type())]); }

    /// @brief Copy all bytes from source buffer to this buffer
    virtual void CopyBufferFrom(const AbstractBuffer& source) = 0;

    /// @brief Fill entire buffer with value, useful for clearing the buffer.
    virtual void FillBuffer(uint8_t value) = 0;

    /// @brief Apply a transformation function on the buffer and ouput result to a destination buffer
    /// @param func Function with the signature void(uint8_t*, uint8_t, uint16_t, uint16_t) that is the transform function
    /// @param destination Destination buffer where transformed bytes will be written to
    virtual void Transform(
        void (&func)(uint8_t* source, uint8_t* destination, uint16_t width, uint16_t height), AbstractBuffer& destination
    ) = 0;

    /// @brief Create a new buffer of the same type. Useful for creating intermediate buffers when applying transformations.
    /// @param width Width of new buffer pixels
    /// @param height Height of new buffer in pixels
    virtual AbstractBuffer* CreateBufferOfSameType(uint16_t width, uint16_t height) = 0;

    // make un-copyable
    AbstractBuffer(const AbstractBuffer&) = delete;
    AbstractBuffer& operator=(const AbstractBuffer&) = delete;
};

/// @brief 3 channel buffer with arrays for red green and blue color
class RGBBuffer : public AbstractBuffer {
  public:
    uint8_t* redChannel;
    uint8_t* greenChannel;
    uint8_t* blueChannel;

    RGBBuffer(uint16_t _width, uint16_t _height);
    ~RGBBuffer();
    BufferType type() const override { return BufferType::RGBBuffer; }

    /// @brief Write a buffer overtop this one
    /// @param newValues
    /// @param xpos
    /// @param ypos
    void Write(const AbstractBuffer& newValues, uint16_t xpos, uint16_t ypos) override;

    /// @brief Fill entire buffer with value, useful for clearing the buffer.
    void FillBuffer(uint8_t value) override;

    /// @brief Apply a transformation function on the buffer and ouput result to a destination buffer
    /// @param func Function with the signature void(uint8_t*, uint8_t, uint16_t, uint16_t) that is the transform function
    /// @param destination Destination buffer where transformed bytes will be written to
    void Transform(
        void (&func)(uint8_t* source, uint8_t* destination, uint16_t width, uint16_t height), AbstractBuffer& destination
    ) override;

    /// @brief Create a new buffer of the same type. Useful for creating intermediate buffers when applying transformations.
    /// @param width Width of new buffer pixels
    /// @param height Height of new buffer in pixels
    AbstractBuffer* CreateBufferOfSameType(uint16_t width, uint16_t height) override;

    void CopyBufferFrom(const AbstractBuffer& source) override;
};

/// @brief 2 channel buffer with arrays for black and red color
class RedBlackBuffer : public AbstractBuffer {
  public:
    uint8_t* redChannel;
    uint8_t* blackChannel;

    RedBlackBuffer(uint16_t _width, uint16_t _height);
    ~RedBlackBuffer();
    BufferType type() const override { return BufferType::AbstractBuffer; }

    /// @brief Write a buffer overtop this one
    /// @param newValues
    /// @param xpos
    /// @param ypos
    void Write(const AbstractBuffer& newValues, uint16_t xpos, uint16_t ypos) override;

    /// @brief Fill entire buffer with value, useful for clearing the buffer.
    void FillBuffer(uint8_t value) override;

    /// @brief Apply a transformation function on the buffer and ouput result to a destination buffer
    /// @param func Function with the signature void(uint8_t*, uint8_t, uint16_t, uint16_t) that is the transform function
    /// @param destination Destination buffer where transformed bytes will be written to
    void Transform(
        void (&func)(uint8_t* source, uint8_t* destination, uint16_t width, uint16_t height), AbstractBuffer& destination
    ) override;

    /// @brief Create a new buffer of the same type. Useful for creating intermediate buffers when applying transformations.
    /// @param width Width of new buffer pixels
    /// @param height Height of new buffer in pixels
    AbstractBuffer* CreateBufferOfSameType(uint16_t width, uint16_t height) override;

    void CopyBufferFrom(const AbstractBuffer& source) override;
};

/// @brief Single channel buffer with a single array for black color
class GrayscaleBuffer : public AbstractBuffer {
  public:
    uint8_t* blackChannel;

    GrayscaleBuffer(uint16_t _width, uint16_t _height);
    ~GrayscaleBuffer();
    BufferType type() const override { return BufferType::GrayscaleBuffer; }

    /// @brief Write a buffer overtop this one
    /// @param newValues
    /// @param xpos
    /// @param ypos
    void Write(const AbstractBuffer& newValues, uint16_t xpos, uint16_t ypos) override;

    /// @brief Fill entire buffer with value, useful for clearing the buffer.
    void FillBuffer(uint8_t value) override;

    /// @brief Apply a transformation function on the buffer and ouput result to a destination buffer
    /// @param func Function with the signature void(uint8_t*, uint8_t, uint16_t, uint16_t) that is the transform function
    /// @param destination Destination buffer where transformed bytes will be written to
    void Transform(
        void (&func)(uint8_t* source, uint8_t* destination, uint16_t width, uint16_t height), AbstractBuffer& destination
    ) override;

    /// @brief Create a new buffer of the same type. Useful for creating intermediate buffers when applying transformations.
    /// @param width Width of new buffer pixels
    /// @param height Height of new buffer in pixels
    AbstractBuffer* CreateBufferOfSameType(uint16_t width, uint16_t height) override;

    void CopyBufferFrom(const AbstractBuffer& source) override;
};

/// @brief Raised when Write(...) is called with an incompatible buffer type
class IncompatibleBufferWrite : public std::runtime_error {
  public:
    explicit IncompatibleBufferWrite(const BufferType destinationBufferType, const BufferType sourceBufferType)
        : std::runtime_error(
              "Incompatible Buffer Write: Unable to write buffer of type " +
              std::string(BufferTypeStrings[static_cast<int>(sourceBufferType)]) + " to " +
              std::string(BufferTypeStrings[static_cast<int>(destinationBufferType)])
          ) {}
};

/// @brief Raised when CopyBufferFrom(...) is called with an incompatible buffer type
class IncompatibleBufferCopy : public std::runtime_error {
  public:
    explicit IncompatibleBufferCopy(const BufferType destinationBufferType, const BufferType sourceBufferType)
        : std::runtime_error(
              "Incompatible Buffer Copy: Unable to copy bytes from buffer of type " +
              std::string(BufferTypeStrings[static_cast<int>(sourceBufferType)]) + " to " +
              std::string(BufferTypeStrings[static_cast<int>(destinationBufferType)])
          ) {}
};

/// @brief Raised when CopyBufferFrom(...) is called with a buffer with the wrong height/width
class MisshapenBufferCopy : public std::runtime_error {
  public:
    explicit MisshapenBufferCopy(const AbstractBuffer& source, const AbstractBuffer& destination)
        : std::runtime_error(
              "Misshapen Buffer Copy: Unable to copy bytes from buffer of dimensions " + std::to_string(source.width) + "x" +
              std::to_string(source.height) + " to destination buffer of dimensions " + std::to_string(destination.width) +
              "x" + std::to_string(destination.height)
          ) {}
};

/// @brief Raised a transformation is attempted on a source buffer and the destination is incompatible
class IncompatibleBufferTransformDestination : public std::runtime_error {
  public:
    explicit IncompatibleBufferTransformDestination(
        const AbstractBuffer& source, const AbstractBuffer& destination, std::string reason
    )
        : std::runtime_error(
              "Incompatiable destination buffer '" + destination.TypeAsString() + "' being written to from source buffer '" +
              source.TypeAsString() + "' - " + reason
          ) {}
};

} // namespace epaperapi