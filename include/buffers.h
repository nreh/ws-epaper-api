#pragma once

#include <stdexcept>
#include <stdint.h>
#include <string>

namespace epaperapi {

class ElementStyle;
namespace utils {
class SupportedPalette;
}

enum class BufferType { AbstractBuffer, RGBBuffer, RedBlackBuffer, GrayscaleBuffer };
static const char* BufferTypeStrings[] = {"AbstractBuffer", "RGBBuffer", "RedBlackBuffer", "GrayscaleBuffer"};

/**
 * @brief A buffer is a block of memory representing a rectangle of pixels.
 *
 * There are different types of buffers depending on the
 * physical capabilities of the device you're trying to draw on. For example, an e-paper display with only grayscale has no
 * need for an RGB buffer - that would be a waste of 2/3 of the bytes we'd allocate.
 *
 * For that reason, each use-case (grayscale, 2-color, RGB, etc...) has a different implementation of the Abstract buffer
 * with different capabilities and limitations for each.
 */
class AbstractBuffer {
  public:
    /// @brief Width of the buffer in pixels
    uint16_t width;
    /// @brief Height of the buffer in pixels
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

    // Some helpful utility functions for drawing shapes and stuff on the buffer

    /// @brief Draw a pixel at a specified x and y position
    /// @param xpos X position in pixels to draw the pixel
    /// @param ypos Y position in pixels to draw the pixel
    /// @param style Pixel will be drawn in this style
    virtual void DrawPixel(uint16_t xpos, uint16_t ypos, const ElementStyle& style) = 0;

    /// @brief Draw pixels on the buffer given a bitmap of 0s and 1s (note, the bitmap is assumed to be packed, ie. each 8
    /// pixels in a byte - 1 bit for each pixel.)
    /// @param xpos X position in pixels to draw the bitmap on the buffer
    /// @param ypos Y position in pixels to draw the bitmap on the buffer
    /// @param width Width of the bitmap in pixels
    /// @param height Height of the bitmap in pixels
    /// @param backgroundStyle 0s in the bitmap will be drawn in this style
    /// @param foregroundStyle 1s in the bitmap will be drawn in this style
    /// @param bitmap Array of packed bitmap data where each bit represents a single pixel
    virtual void DrawBitmap(
        uint16_t xpos,
        uint16_t ypos,
        uint16_t width,
        uint16_t height,
        const ElementStyle& backgroundStyle,
        const ElementStyle& foregroundStyle,
        const uint8_t* bitmap
    ) = 0;

    /// @brief Draw a filled rectangle on the buffer
    /// @param xpos X position in pixels of the upper left corner of the rectangle
    /// @param ypos Y position in pixels of the upper left corner of the rectangle
    /// @param width Width of the rectangle in pixels
    /// @param height Height of the rectangle in pixels
    /// @param style How to color/style the rectangle
    virtual void
    DrawFilledRectangle(uint16_t xpos, uint16_t ypos, uint16_t width, uint16_t height, const ElementStyle& style) = 0;

    /// @brief Draw a line on the buffer
    /// @param xpos_1 X position of the start point of the line
    /// @param ypos_1 Y position of the start point of the line
    /// @param xpos_2 X position of the end point of the line
    /// @param ypos_2 Y position of the end point of the line
    /// @param style How the color/style the line
    virtual void DrawLine(uint16_t xpos_1, uint16_t ypos_1, uint16_t xpos_2, uint16_t ypos_2, const ElementStyle& style) = 0;
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

    /// @brief Draw a pixel at a specified x and y position
    /// @param xpos X position in pixels to draw the pixel
    /// @param ypos Y position in pixels to draw the pixel
    /// @param style Pixel will be drawn in this style
    void DrawPixel(uint16_t xpos, uint16_t ypos, const ElementStyle& style) override;

    /// @brief Draw pixels on the buffer given a bitmap of 0s and 1s (note, the bitmap is assumed to be packed, ie. each 8
    /// pixels in a byte - 1 bit for each pixel.)
    /// @param xpos X position in pixels to draw the bitmap on the buffer
    /// @param ypos Y position in pixels to draw the bitmap on the buffer
    /// @param width Width of the bitmap in pixels
    /// @param height Height of the bitmap in pixels
    /// @param backgroundStyle 0s in the bitmap will be drawn in this style
    /// @param foregroundStyle 1s in the bitmap will be drawn in this style
    /// @param bitmap Array of packed bitmap data where each bit represents a single pixel
    void DrawBitmap(
        uint16_t xpos,
        uint16_t ypos,
        uint16_t width,
        uint16_t height,
        const ElementStyle& backgroundStyle,
        const ElementStyle& foregroundStyle,
        const uint8_t* bitmap
    ) override;

    /// @brief Draw a filled rectangle on the buffer
    /// @param xpos X position in pixels of the upper left corner of the rectangle
    /// @param ypos Y position in pixels of the upper left corner of the rectangle
    /// @param width Width of the rectangle in pixels
    /// @param height Height of the rectangle in pixels
    /// @param style How to color/style the rectangle
    void
    DrawFilledRectangle(uint16_t xpos, uint16_t ypos, uint16_t width, uint16_t height, const ElementStyle& style) override;

    /// @brief Draw a line on the buffer
    /// @param xpos_1 X position of the start point of the line
    /// @param ypos_1 Y position of the start point of the line
    /// @param xpos_2 X position of the end point of the line
    /// @param ypos_2 Y position of the end point of the line
    /// @param style How the color/style the line
    void DrawLine(uint16_t xpos_1, uint16_t ypos_1, uint16_t xpos_2, uint16_t ypos_2, const ElementStyle& style) override;

    /// @brief Converts this RGB buffer to a 4 color (2 bit color) array with the color palette: black, white, yellow red
    /// @param dest Destination array to write pixel data to
    void ConvertTo4Color(uint8_t* dest);

    /// @brief Converts this RGB buffer to a 6 color (4 bit color) array with the color palette: black, white, yellow red,
    /// blue, green
    /// @param dest Destination array to write pixel data to
    void ConvertTo6Color(uint8_t* dest);

    /// @brief Does the same thing as ConvertTo6Color() but is possibly better due to thresholding rather than hard coding
    /// colors.
    /// @param dest Destination array to write pixel data to
    void ConvertTo6Color_Variant2(uint8_t* dest);

    /// @brief Converts this RGB buffer to a 7 color (4 bit color) array
    /// @param dest Destination array to write pixel data to
    void ConvertTo7Color(uint8_t* dest);

    /// @brief Writes the RGB buffer to a destination array in 2 bit color format with a predefined palette of supported
    /// colors
    /// @param dest Destination array to write pixel data to
    /// @param palette Supported colors that can be drawn on the display
    void Quantize2Bit(uint8_t* dest, const utils::SupportedPalette& palette);

    /// @brief Writes the RGB buffer to a destination array in 4 bit color format with a predefined palette of supported
    /// colors
    /// @param dest Destination array to write pixel data to
    /// @param palette Supported colors that can be drawn on the display
    void Quantize4Bit(uint8_t* dest, const utils::SupportedPalette& palette);
};

/// @brief 2 channel buffer with arrays for black and red color
class RedBlackBuffer : public AbstractBuffer {
  public:
    uint8_t* redChannel;
    uint8_t* blackChannel;

    RedBlackBuffer(uint16_t _width, uint16_t _height);
    ~RedBlackBuffer();
    BufferType type() const override { return BufferType::RedBlackBuffer; }

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

    /// @brief Draw a pixel at a specified x and y position
    /// @param xpos X position in pixels to draw the pixel
    /// @param ypos Y position in pixels to draw the pixel
    /// @param style Pixel will be drawn in this style
    void DrawPixel(uint16_t xpos, uint16_t ypos, const ElementStyle& style) override;

    /// @brief Draw pixels on the buffer given a bitmap of 0s and 1s (note, the bitmap is assumed to be packed, ie. each 8
    /// pixels in a byte - 1 bit for each pixel.)
    /// @param xpos X position in pixels to draw the bitmap on the buffer
    /// @param ypos Y position in pixels to draw the bitmap on the buffer
    /// @param width Width of the bitmap in pixels
    /// @param height Height of the bitmap in pixels
    /// @param backgroundStyle 0s in the bitmap will be drawn in this style
    /// @param foregroundStyle 1s in the bitmap will be drawn in this style
    /// @param bitmap Array of packed bitmap data where each bit represents a single pixel
    void DrawBitmap(
        uint16_t xpos,
        uint16_t ypos,
        uint16_t width,
        uint16_t height,
        const ElementStyle& backgroundStyle,
        const ElementStyle& foregroundStyle,
        const uint8_t* bitmap
    ) override;

    /// @brief Draw a filled rectangle on the buffer
    /// @param xpos X position in pixels of the upper left corner of the rectangle
    /// @param ypos Y position in pixels of the upper left corner of the rectangle
    /// @param width Width of the rectangle in pixels
    /// @param height Height of the rectangle in pixels
    /// @param style How to color/style the rectangle
    void
    DrawFilledRectangle(uint16_t xpos, uint16_t ypos, uint16_t width, uint16_t height, const ElementStyle& style) override;

    /// @brief Draw a line on the buffer
    /// @param xpos_1 X position of the start point of the line
    /// @param ypos_1 Y position of the start point of the line
    /// @param xpos_2 X position of the end point of the line
    /// @param ypos_2 Y position of the end point of the line
    /// @param style How the color/style the line
    void DrawLine(uint16_t xpos_1, uint16_t ypos_1, uint16_t xpos_2, uint16_t ypos_2, const ElementStyle& style) override;
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

    /// @brief Draw a pixel at a specified x and y position
    /// @param xpos X position in pixels to draw the pixel
    /// @param ypos Y position in pixels to draw the pixel
    /// @param style Pixel will be drawn in this style
    void DrawPixel(uint16_t xpos, uint16_t ypos, const ElementStyle& style) override;

    /// @brief Draw pixels on the buffer given a bitmap of 0s and 1s (note, the bitmap is assumed to be packed, ie. each 8
    /// pixels in a byte - 1 bit for each pixel.)
    /// @param xpos X position in pixels to draw the bitmap on the buffer
    /// @param ypos Y position in pixels to draw the bitmap on the buffer
    /// @param width Width of the bitmap in pixels
    /// @param height Height of the bitmap in pixels
    /// @param backgroundStyle 0s in the bitmap will be drawn in this style
    /// @param foregroundStyle 1s in the bitmap will be drawn in this style
    /// @param bitmap Array of packed bitmap data where each bit represents a single pixel
    void DrawBitmap(
        uint16_t xpos,
        uint16_t ypos,
        uint16_t width,
        uint16_t height,
        const ElementStyle& backgroundStyle,
        const ElementStyle& foregroundStyle,
        const uint8_t* bitmap
    ) override;

    /// @brief Draw a filled rectangle on the buffer
    /// @param xpos X position in pixels of the upper left corner of the rectangle
    /// @param ypos Y position in pixels of the upper left corner of the rectangle
    /// @param width Width of the rectangle in pixels
    /// @param height Height of the rectangle in pixels
    /// @param style How to color/style the rectangle
    void
    DrawFilledRectangle(uint16_t xpos, uint16_t ypos, uint16_t width, uint16_t height, const ElementStyle& style) override;

    /// @brief Draw a line on the buffer
    /// @param xpos_1 X position of the start point of the line
    /// @param ypos_1 Y position of the start point of the line
    /// @param xpos_2 X position of the end point of the line
    /// @param ypos_2 Y position of the end point of the line
    /// @param style How the color/style the line
    void DrawLine(uint16_t xpos_1, uint16_t ypos_1, uint16_t xpos_2, uint16_t ypos_2, const ElementStyle& style) override;

    /// @brief Converts this buffer to a 1 bit black/white array.
    /// @param dest Destination array to write pixel data to
    void ConvertTo1Bit(uint8_t* dest);

    /// @brief Converts this buffer to a 2 bit, 4 shades of grayscale, array.
    /// @param dest Destination array to write pixel data to
    void ConvertTo2Bit(uint8_t* dest);
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