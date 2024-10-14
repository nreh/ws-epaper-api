#pragma once

#include <stdint.h>
#include <string>

namespace epaperapi {
/// @brief Namespace containing fonts for drawing text
namespace fonts {

/// @brief A datastructure containing pixel data on characters of a font of a single size. Can be used to draw text on a
/// DrawTarget.
class AbstractFont {
  public:
    /// @brief Get font size in pt
    virtual uint8_t GetFontSize() const = 0;

    /// @brief Get the height of a single character in pixels
    virtual uint8_t GetHeight() const = 0;

    /// @brief Get the name of the font
    virtual std::string GetFontName() = 0;

    /// @brief Get complete set of supported characters by this font
    virtual std::string GetCharacterSet() const = 0;

    /// @brief Get pointer to array containing bitmap data
    virtual const uint8_t* GetBitmapData() const = 0;

    /// @brief Get pointer to array containing character widths
    virtual const uint8_t* GetCharacterWidths() const = 0;

    /// @brief Returns true if the character exists in the font's character set
    bool SupportsCharacter(char character) { return GetCharacterSet().find(character) != std::string::npos; }

    const inline int getCharsetIndex(char character) const {
        auto f = GetCharacterSet().find(character);
        if (f == std::string::npos) {
            return 0;
        }
        return f;
    }

    /// @brief Get width of a character
    const uint8_t GetCharacterWidth(char character) const {
        auto f = GetCharacterSet().find(character);
        if (f == std::string::npos) {
            return 0;
        }

        return GetCharacterWidths()[f];
    }

    /// @brief Get a bitmap of the the given character, if that character isn't found, `nullptr` is returned instead.
    const uint8_t* GetCharacterBitmap(char character) const {
        auto f = GetCharacterSet().find(character);
        if (f == std::string::npos) {
            return nullptr;
        }

        int offset = 0;
        for (int i = 0; i < f; i++) {
            auto bits = GetCharacterWidths()[i] * GetHeight();
            offset += bits % 8 == 0 ? bits / 8 : bits / 8 + 1; // account for padding
        }

        return GetBitmapData() + offset;
    }
};

} // namespace fonts
} // namespace epaperapi