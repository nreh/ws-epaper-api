#include "../debug.h"
#include "../elements.h"
#include "../fonts/AbstractFont.h"

#include <string>

namespace epaperapi::elements {

/// @brief Element for drawing text using a font
template <class Font> class TextElement : public AbstractElement {
  public:
    static_assert(
        std::is_base_of<fonts::AbstractFont, Font>::value,
        "TextElement Font must derive from AbstractFont. Are you sure you passed in a valid font class?"
    );
    const fonts::AbstractFont* textFont = nullptr;

    /// @brief The style of foreground of the text
    ElementStyle foregroundStyle;

    /// @brief The style of the background of the text
    ElementStyle backgroundStyle = ElementStyle::TransparentStyle();

    /// @brief Number of pixels between each character, can be negative.
    int8_t characterSpacing = 0;

    TextElement() : textFont(new Font()) {}
    TextElement(std::string text) : text(text), textFont(new Font()) {}
    ~TextElement() {
        if (textFont != nullptr) {
            delete textFont;
            textFont = nullptr;
        }
    }

    /// @brief Text to be displayed
    std::string text = "Text Element";

    /// @brief Get the width of the text to be rendered in pixels
    uint16_t GetWidth() {
        auto widths = textFont->GetCharacterWidths();
        uint16_t totalWidth = 0;

        for (int i = 0; i < text.length(); i++) {
            totalWidth += widths[textFont->getCharsetIndex(text[i])];
        }

        totalWidth -= characterSpacing * (text.length() - 1);

        return totalWidth;
    }

    /// @brief Get the height of the text to be rendered in pixels
    uint16_t GetHeight() { return textFont->GetHeight(); }

  private:
    /// @brief Draw a single character on the target buffer at the specified x position
    /// @param target Target buffer to draw on
    /// @param character Character to draw
    /// @param bufferXpos X Position on buffer
    /// @returns Width of the drawn character
    uint8_t DrawCharacter(AbstractBuffer& target, char character, uint16_t bufferXpos) {
        const uint8_t* chardata = textFont->GetCharacterBitmap(character);

        if (chardata == nullptr) {
            return 0; // character not supported by font
        }

        auto width = textFont->GetCharacterWidth(character);

        target.DrawBitmap(bufferXpos, ypos, width, textFont->GetHeight(), backgroundStyle, foregroundStyle, chardata);

        return width;
    }

  public:
    void Draw(AbstractBuffer& target) override {
        uint16_t bufferXpos = xpos;
        for (int i = 0; i < text.length(); i++) {
            // draw character
            bufferXpos += DrawCharacter(target, text[i], bufferXpos);
            bufferXpos += characterSpacing;
        }
    }
};

} // namespace epaperapi::elements