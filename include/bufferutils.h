#pragma once

#include "buffers.h"
#include <cstring>
#include <stdint.h>

/**
 * Helper functions to perform operations on Buffers
 */

namespace epaperapi {

enum class BufferTransform {
    /// @brief Perform no transformation on the buffer
    None,

    /// @brief Rotate the buffer 90 degreees clockwise
    Rotate90Clockwise,

    /// @brief Rotate the buffer 90 degrees counter-clockwise
    Rotate90CounterClockwise,

    /// @brief Rotate the buffer 180 degrees
    Rotate180
};

namespace utils {

/**
 * @brief Posterizes a GrayscaleBuffer for displays that have a limited grayscale capability. For example, a step size of 2
 * result in a buffer with values that are either 0 or 255.
 *
 * @param grayscale The GrayScale buffer to posterize. Note, this will modify the internal grayscale buffer of this object.
 * @param steps The grayscale steps, must be >= 2 and <= 255. If an invalid value is given, the function will not do
 * anything.
 */
inline void PosterizeGrayscale(GrayscaleBuffer& grayscale, uint8_t steps) {
    if (steps < 2) {
        return;
    }

    uint8_t interval = 255 / (steps - 1);

    for (int i = 0; i < grayscale.width * grayscale.height; i++) {
        auto val = grayscale.blackChannel[i];
        if (val == 0 || val == 255)
            continue; // black and white should never be changed
        grayscale.blackChannel[i] = (val * (steps - 1) + 127) / 255 * interval;
    }
}

/// @brief Packs an array of bytes so that each byte holds 8 horizontal pixels. This also eliminates any grayscale, any value
/// less than 255 is clamped to zero.
/// @param pixelsArray Array of pixels to pack
/// @param packedPixelsArray Results of packing will be written to this array. Each row in this array is (pixelsArray.width /
/// 8) bytes and is rounded up to make sure all pixels can fit.
/// @param width Width of image
/// @param height
inline void Pack1Bit(uint8_t* pixelsArray, uint8_t* packedPixelsArray, uint16_t width, uint16_t height) {
    uint16_t packedBytesWidth = width % 8 == 0 ? width / 8 : width / 8 + 1;

    uint16_t verticalPos = 0;

    for (uint16_t y = 0; y < height; y++) {
        for (uint16_t x = 0; x < width; x++) {
            // pack 8 pixels into 1 byte
            auto val = pixelsArray[y * width + x];
            if (val == 255) {
                packedPixelsArray[verticalPos + (x / 8)] |= (1 << (7 - (x % 8))); // write 1
            } else {
                packedPixelsArray[verticalPos + (x / 8)] &= ~(1 << (7 - (x % 8))); // write 0
            }
        }
        verticalPos += packedBytesWidth;
    }
}

inline void RotateMatrix90Clockwise(uint8_t* source, uint8_t* destination, uint16_t width, uint16_t height) {
    uint16_t dest_j, dest_i;

    for (int j = 0; j < height; j++) {
        dest_i = height - 1 - j;
        for (int i = 0; i < width; i++) {
            dest_j = i;
            destination[height * dest_j + dest_i] = source[width * j + i];
        }
    }
}

inline void RotateMatrix90CounterClockwise(uint8_t* source, uint8_t* destination, uint16_t width, uint16_t height) {
    uint16_t dest_j, dest_i;

    for (int j = 0; j < height; j++) {
        dest_i = j;
        for (int i = 0; i < width; i++) {
            dest_j = width - 1 - i;
            destination[height * dest_j + dest_i] = source[width * j + i];
        }
    }
}

inline void RotateMatrix180(uint8_t* source, uint8_t* destination, uint16_t width, uint16_t height) {
    uint16_t dest_j, dest_i;

    for (int j = 0; j < height; j++) {
        dest_j = height - 1 - j;
        for (int i = 0; i < width; i++) {
            dest_i = width - 1 - i;
            destination[width * dest_j + dest_i] = source[width * j + i];
        }
    }
}

/// @brief Apply a transformation on a buffer and output the result to a destination buffer. Makes sure both buffers are
/// compatible.
/// @param source Buffer to perform the transformation on
/// @param destination Buffer to output the results to
/// @param transformation Transformation to perform
inline void TransformBuffer(AbstractBuffer& source, AbstractBuffer& destination, BufferTransform transformation) {
    if (source.type() != destination.type()) {
        throw IncompatibleBufferTransformDestination(source, destination, "Incompatible type");
    }

    void (*func)(uint8_t* source, uint8_t* destination, uint16_t width, uint16_t height) =
        nullptr; // transformation function

    if (transformation == BufferTransform::None) {
        return;
    } else if (transformation == BufferTransform::Rotate90Clockwise) {
        if (destination.width != source.height && destination.height != source.width) {
            throw IncompatibleBufferTransformDestination(
                source, destination, "Incompatible destination shape for 90 degree rotation"
            );
        }
        func = &RotateMatrix90Clockwise;
    } else if (transformation == BufferTransform::Rotate90CounterClockwise) {
        if (destination.width != source.height && destination.height != source.width) {
            throw IncompatibleBufferTransformDestination(
                source, destination, "Incompatible destination shape for 90 degree rotation"
            );
        }
        func = &RotateMatrix90CounterClockwise;
    } else if (transformation == BufferTransform::Rotate180) {
        if (destination.height != source.height && destination.width != source.width) {
            throw IncompatibleBufferTransformDestination(
                source, destination, "Incompatible destination shape for 180 degree rotation"
            );
        }
        func = &RotateMatrix180;
    }

    if (func == nullptr) {
        return; // no transformation function found
    }

    source.Transform(*func, destination);
}

// RGB buffer operations - (thanks ChatGPT!)

// Convert RGBBuffer to 1-bit monochrome (black & white)
inline void convertToMonochrome(const RGBBuffer& buffer, uint8_t* output) {
    uint16_t width = buffer.width;
    uint16_t height = buffer.height;
    int byteWidth = (width + 7) / 8;
    memset(output, 0, byteWidth * height);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int idx = y * width + x;
            uint8_t red = buffer.redChannel[idx];
            uint8_t green = buffer.greenChannel[idx];
            uint8_t blue = buffer.blueChannel[idx];
            uint8_t brightness = (red + green + blue) / 3;
            if (brightness > 127) {
                output[y * byteWidth + (x / 8)] |= (0x80 >> (x % 8));
            }
        }
    }
}

// Convert RGBBuffer to 4-bit grayscale
inline void convertTo4BitGrayscale(const RGBBuffer& buffer, uint8_t* output) {
    uint16_t width = buffer.width;
    uint16_t height = buffer.height;
    int byteWidth = (width + 1) / 2;
    memset(output, 0, byteWidth * height);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int idx = y * width + x;
            uint8_t red = buffer.redChannel[idx];
            uint8_t green = buffer.greenChannel[idx];
            uint8_t blue = buffer.blueChannel[idx];
            uint8_t brightness = (red + green + blue) / 3;
            uint8_t grayscale = brightness / 17; // Scale to 0-15

            if (x % 2 == 0) {
                output[y * byteWidth + (x / 2)] |= (grayscale << 4);
            } else {
                output[y * byteWidth + (x / 2)] |= grayscale;
            }
        }
    }
}

// Convert RGBBuffer to 4-bit color (16 colors)
inline void convertTo4BitColor(const RGBBuffer& buffer, uint8_t* output) {
    uint16_t width = buffer.width;
    uint16_t height = buffer.height;
    int byteWidth = (width + 1) / 2;
    memset(output, 0, byteWidth * height);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int idx = y * width + x;
            uint8_t red = buffer.redChannel[idx];
            uint8_t green = buffer.greenChannel[idx];
            uint8_t blue = buffer.blueChannel[idx];
            uint8_t colorIdx = 0;

            // Simple color quantization to 4-bit color index
            if (red > 127)
                colorIdx |= 0b1000;
            if (green > 127)
                colorIdx |= 0b0100;
            if (blue > 127)
                colorIdx |= 0b0010;

            if (x % 2 == 0) {
                output[y * byteWidth + (x / 2)] |= (colorIdx << 4);
            } else {
                output[y * byteWidth + (x / 2)] |= colorIdx;
            }
        }
    }
}

// Convert RGBBuffer to 8-bit RGB (256 colors)
inline void convertTo8BitRGB(const RGBBuffer& buffer, uint8_t* output) {
    uint16_t width = buffer.width;
    int height = buffer.height;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int idx = y * width + x;
            uint8_t red = buffer.redChannel[idx] >> 5;     // 3 bits
            uint8_t green = buffer.greenChannel[idx] >> 5; // 3 bits
            uint8_t blue = buffer.blueChannel[idx] >> 6;   // 2 bits

            output[idx] = (red << 5) | (green << 2) | blue;
        }
    }
}

// Convert RGBBuffer to 16-bit RGB (5-6-5 format)
inline void convertTo16BitRGB(const RGBBuffer& buffer, uint8_t* output) {
    uint16_t width = buffer.width;
    uint16_t height = buffer.height;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int idx = y * width + x;
            uint8_t red = buffer.redChannel[idx] >> 3;     // 5 bits
            uint8_t green = buffer.greenChannel[idx] >> 2; // 6 bits
            uint8_t blue = buffer.blueChannel[idx] >> 3;   // 5 bits

            output[2 * idx] = ((red << 3) | (green >> 3)) & 0xFF;
            output[2 * idx + 1] = ((green << 5) | blue) & 0xFF;
        }
    }
}

} // namespace utils
} // namespace epaperapi