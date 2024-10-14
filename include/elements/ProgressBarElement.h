#include "../elements.h"

namespace epaperapi::elements {
/// @brief A horizontal progress bar that shows a percentage
class ProgressBarElement : public AbstractElement {
  public:
    enum class Variants { SimpleRounded, Skeuomorphic };
    Variants variant = Variants::SimpleRounded;
    float progress = 0;
    uint16_t width = 25;

    ElementStyle backgroundStyle = ElementStyle(255);
    ElementStyle foregroundStyle = ElementStyle(0);

  private:
    void DrawSimpleRounded(AbstractBuffer& target) {
        const uint16_t height = 7;

        // Draw rounded rectangle container

        target.DrawLine(xpos + 2, ypos, xpos + width - 1, ypos, foregroundStyle);
        target.DrawLine(xpos + 2, ypos + height - 1, xpos + width - 1, ypos + height - 1, foregroundStyle);
        target.DrawLine(xpos, ypos + 2, xpos, ypos + height - 2, foregroundStyle);
        target.DrawLine(xpos + width, ypos + 2, xpos + width, ypos + height - 2, foregroundStyle);

        target.DrawPixel(xpos + 1, ypos + 1, foregroundStyle);
        target.DrawPixel(xpos + width - 1, ypos + 1, foregroundStyle);
        target.DrawPixel(xpos + width - 1, ypos + height - 2, foregroundStyle);
        target.DrawPixel(xpos + 1, ypos + height - 2, foregroundStyle);

        // fill progress
        if (progress == 0) {
            return;
        }
        uint16_t progressWidth = (width - 2) * progress;
        target.DrawFilledRectangle(xpos + 2, ypos + 1, progressWidth, height - 2, foregroundStyle);
        target.DrawLine(xpos + 1, ypos + 2, xpos + 1, ypos + 5, foregroundStyle);
        target.DrawLine(xpos + progressWidth + 2, ypos + 2, xpos + progressWidth + 2, ypos + 5, foregroundStyle);
    }

    void DrawSkeuomorphic(AbstractBuffer& target) {
        DrawSimpleRounded(target);

        if (progress == 0) {
            return;
        }

        uint16_t progressWidth = (width - 2) * progress;
        target.DrawLine(xpos + 2, ypos + 2, xpos + progressWidth + 1, ypos + 2, backgroundStyle);
    }

  public:
    void Draw(AbstractBuffer& target) override {
        switch (variant) {
        case Variants::SimpleRounded:
            DrawSimpleRounded(target);
            break;
        case Variants::Skeuomorphic:
            DrawSkeuomorphic(target);
            break;
        default:
            break;
        }
    }
};
} // namespace epaperapi::elements