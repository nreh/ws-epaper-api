#pragma once

#include <stdint.h>

namespace epaperapi {

static inline uint8_t BlendPixel(uint8_t foreground, uint8_t background, float alpha) {
    return alpha * foreground + (background * (1 - alpha));
}

} // namespace epaperapi