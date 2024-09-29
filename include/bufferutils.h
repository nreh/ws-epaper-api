#pragma once

#include "buffers.h"
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
        for (int i = 0; i < width; i++) {
            dest_j = i;
            dest_i = height - 1 - j;
            destination[height * dest_j + dest_i] = source[width * j + i];
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
        func = &RotateMatrix90Clockwise;
    } else if (transformation == BufferTransform::Rotate90CounterClockwise) {
        // todo: implement 90 counterclockwise transformation
    } else if (transformation == BufferTransform::Rotate180) {
        // todo: implement 180 transformation
    }

    if (func == nullptr) {
        return; // no transformation function found
    }

    source.Transform(*func, destination);
}

} // namespace utils
} // namespace epaperapi