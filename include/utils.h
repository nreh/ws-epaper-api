#pragma once

#include <stdint.h>

namespace epaperapi {

namespace utils {
/// @brief Blend 2 pixels together by taking a weighted average based on alpha of the two pixels.
/// @param foreground Foreground pixel value
/// @param background Background pixel value
/// @param alpha
/// @return
static inline uint8_t BlendPixel(uint8_t foreground, uint8_t background, float alpha) {
    return alpha * foreground + (background * (1 - alpha));
}

/// @brief Returns the larger of two alpha values
/// @param foreground_alpha Foreground pixel alpha
/// @param background_alpha Background pixel alpha
/// @return
static inline float BlendAlpha(float foreground_alpha, float background_alpha) {
    return std::max(foreground_alpha, background_alpha);
}
} // namespace utils
} // namespace epaperapi