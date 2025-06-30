#pragma once

#include "buffers.h"
#include <cstring>
#include <limits>
#include <stdint.h>
#include <vector>

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
    memset(packedPixelsArray, 0, height * packedBytesWidth);

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

template <typename T> inline void RotateMatrix90Clockwise(T* source, T* destination, uint16_t width, uint16_t height) {
    uint16_t dest_j, dest_i;

    for (int j = 0; j < height; j++) {
        dest_i = height - 1 - j;
        for (int i = 0; i < width; i++) {
            dest_j = i;
            destination[height * dest_j + dest_i] = source[width * j + i];
        }
    }
}

template <typename T>
inline void RotateMatrix90CounterClockwise(T* source, T* destination, uint16_t width, uint16_t height) {
    uint16_t dest_j, dest_i;

    for (int j = 0; j < height; j++) {
        dest_i = j;
        for (int i = 0; i < width; i++) {
            dest_j = width - 1 - i;
            destination[height * dest_j + dest_i] = source[width * j + i];
        }
    }
}

template <typename T> inline void RotateMatrix180(T* source, T* destination, uint16_t width, uint16_t height) {
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
    void (*funcAlpha)(float* source, float* destination, uint16_t width, uint16_t height) =
        nullptr; // transformation function but for the alpha channel

    if (transformation == BufferTransform::None) {
        return;
    } else if (transformation == BufferTransform::Rotate90Clockwise) {
        if (destination.width != source.height && destination.height != source.width) {
            throw IncompatibleBufferTransformDestination(
                source, destination, "Incompatible destination shape for 90 degree rotation"
            );
        }
        func = &RotateMatrix90Clockwise<uint8_t>;
        funcAlpha = &RotateMatrix90Clockwise<float>;
    } else if (transformation == BufferTransform::Rotate90CounterClockwise) {
        if (destination.width != source.height && destination.height != source.width) {
            throw IncompatibleBufferTransformDestination(
                source, destination, "Incompatible destination shape for 90 degree rotation"
            );
        }
        func = &RotateMatrix90CounterClockwise<uint8_t>;
        funcAlpha = &RotateMatrix90CounterClockwise<float>;
    } else if (transformation == BufferTransform::Rotate180) {
        if (destination.height != source.height && destination.width != source.width) {
            throw IncompatibleBufferTransformDestination(
                source, destination, "Incompatible destination shape for 180 degree rotation"
            );
        }
        func = &RotateMatrix180<uint8_t>;
        funcAlpha = &RotateMatrix180<float>;
    }

    if (func == nullptr) {
        return; // no transformation function found
    }

    source.Transform(*func, destination);

    // the Transform() function doesn't work on the alpha channel, we must do it here manually.
    source.TransformAlpha(*funcAlpha, destination);
}
struct RGB {
    uint8_t r, g, b;
    RGB(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}
};

/// @brief Represents colors that an EPD display supports
class SupportedPalette {
  private:
    std::vector<RGB> colors;

    SupportedPalette(std::vector<RGB> colors) : colors(colors) {}

  public:
    /// @brief Given an RGB color, returns the index of the nearest supported color
    uint8_t GetNearestColor(const uint8_t& r, const uint8_t& g, const uint8_t& b) const {
        uint8_t nearestIndex = 0;
        uint32_t smallestDistanceSquared = std::numeric_limits<uint32_t>::max();

        uint8_t i = 0;
        for (const auto& c : colors) {
            if (c.r == r && c.g == g && c.b == b) {
                return i;
            }
            i++;
        }

        for (i = 0; i < colors.size(); ++i) {
            uint32_t distanceSquared = (r - colors[i].r) * (r - colors[i].r) + (g - colors[i].g) * (g - colors[i].g) +
                                       (b - colors[i].b) * (b - colors[i].b);

            if (distanceSquared < smallestDistanceSquared) {
                smallestDistanceSquared = distanceSquared;
                nearestIndex = i;
            }
        }

        return nearestIndex;
    }

    /// @brief Generate supported colors for 7 color displays (Black, White, Green, Blue, Red, Yellow, Orange)
    static SupportedPalette Make7Color() {
        return SupportedPalette({
            RGB(0, 0, 0),       // Black
            RGB(255, 255, 255), // White
            RGB(0, 255, 0),     // Green
            RGB(0, 0, 255),     // Blue
            RGB(255, 0, 0),     // Red
            RGB(255, 255, 0),   // Yellow
            RGB(255, 128, 0)    // Orange
        });
    }

    /// @brief Generate supported colors for 6 color displays (Black, White, Yellow, Red, Blue, Green)
    static SupportedPalette Make6Color() {
        return SupportedPalette({
            RGB(0, 0, 0),       // Black
            RGB(255, 255, 255), // White
            RGB(255, 255, 0),   // Yellow
            RGB(255, 0, 0),     // Red
            RGB(0, 0, 255),     // Blue
            RGB(0, 255, 0)      // Green
        });
    }

    /// @brief Generate supported colors for 4 color displays (Black, White, Yellow, Red)
    static SupportedPalette Make4Color() {
        return SupportedPalette({
            RGB(0, 0, 0),       // Black
            RGB(255, 255, 255), // White
            RGB(255, 255, 0),   // Yellow
            RGB(255, 0, 0)      // Red
        });
    }
};

} // namespace utils
} // namespace epaperapi