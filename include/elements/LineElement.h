#include "../elements.h"

namespace epaperapi::elements {

/// @brief A simple line
class LineElement : public AbstractElement {
  public:
    uint16_t xpos_2, ypos_2;

    LineElement(uint16_t xpos_1, uint16_t ypos_1, uint16_t xpos_2, uint16_t ypos_2)
        : xpos_2(xpos_2), ypos_2(ypos_2), AbstractElement(xpos_1, ypos_1) {}

    /// @brief Draw the FilledRectangle to the target buffer
    /// @param target Buffer that this Filled Rectangle will be Drawn on to
    void Draw(AbstractBuffer& target) override { target.DrawLine(xpos, ypos, xpos_2, ypos_2, style); }
};

} // namespace epaperapi::elements