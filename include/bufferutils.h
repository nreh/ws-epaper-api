#pragma once

#include "buffers.h"
#include <stdint.h>

/**
 * Helper functions to perform operations on Buffers
 */

namespace epaperapi {

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
} // namespace utils
} // namespace epaperapi