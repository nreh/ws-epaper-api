#include "../bitmaps/AbstractBitmap.h"
#include "../elements.h"

namespace epaperapi::elements {
/// @brief Element that renders a bitmap image
class Bitmap1BitElement : public AbstractElement {
  public:
    bitmaps::AbstractBitmap* bitmap;
    ElementStyle backgroundStyle = ElementStyle::TransparentStyle();
    ElementStyle foregroundStyle = ElementStyle(0);

    Bitmap1BitElement(uint16_t xpos, uint16_t ypos, bitmaps::AbstractBitmap* bitmap)
        : bitmap(bitmap), AbstractElement(xpos, ypos) {}

    void Draw(AbstractBuffer& target) override {
        target.DrawBitmap(
            xpos, ypos, bitmap->GetWidth(), bitmap->GetHeight(), backgroundStyle, foregroundStyle, bitmap->GetBitmapData()
        );
    }
};
} // namespace epaperapi::elements