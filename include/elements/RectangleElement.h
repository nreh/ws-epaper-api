#include "../elements.h"

namespace epaperapi::elements {

/// @brief A simple rectangle with a fill and border style
class RectangleElement : public AbstractElement {
  public:
    uint16_t width, height;

    /// @brief The style of the filled rectangle
    ElementStyle fillStyle = ElementStyle(0, 0, 0);

    /// @brief The style of the borders of the rectangle
    ElementStyle borderStyle = ElementStyle::TransparentStyle();

    RectangleElement(uint16_t width, uint16_t height) : width(width), height(height) {}
    RectangleElement(uint16_t width, uint16_t height, uint16_t xpos, uint16_t ypos)
        : width(width), height(height), AbstractElement(xpos, ypos) {}

    /// @brief Draw the FilledRectangle to the target buffer
    /// @param target Buffer that this Filled Rectangle will be Drawn on to
    void Draw(AbstractBuffer& target) override {
        target.DrawFilledRectangle(xpos, ypos, width, height, fillStyle);
        target.DrawRectangle(xpos, ypos, width, height, borderStyle);
    }
};

} // namespace epaperapi::elements