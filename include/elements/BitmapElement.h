#include "../bitmaps/AbstractBitmap.h"
#include "../elements.h"

namespace epaperapi::elements {
/// @brief Element that renders a bitmap image
class BitmapElement : public AbstractElement {
  private:
    const bitmaps::AbstractBitmap& bitmap;

  public:
    ElementStyle backgroundStyle = ElementStyle::TransparentStyle();
    ElementStyle foregroundStyle = ElementStyle(0);

    BitmapElement(uint16_t xpos, uint16_t ypos, const bitmaps::AbstractBitmap& bitmap)
        : bitmap(bitmap), AbstractElement(xpos, ypos) {}

    void Draw(AbstractBuffer& target) override {
        target.DrawBitmap(
            xpos, ypos, bitmap.GetWidth(), bitmap.GetHeight(), backgroundStyle, foregroundStyle, bitmap.GetBitmapData()
        );
    }
};
} // namespace epaperapi::elements