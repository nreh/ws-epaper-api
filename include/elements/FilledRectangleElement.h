#include "../elements.h"

namespace epaperapi::elements {

/// @brief A simple filled rectangle
class FilledRectangleElement : public AbstractElement {
  public:
    uint16_t width, height;

    FilledRectangleElement(uint16_t width, uint16_t height) : width(width), height(height) {}
    FilledRectangleElement(uint16_t width, uint16_t height, uint16_t xpos, uint16_t ypos)
        : width(width), height(height), AbstractElement(xpos, ypos) {}

    /// @brief Draw the FilledRectangle to the target buffer
    /// @param target Buffer that this Filled Rectangle will be Drawn on to
    void Draw(AbstractBuffer& target) override { target.DrawFilledRectangle(xpos, ypos, width, height, style); }
};

} // namespace epaperapi::elements