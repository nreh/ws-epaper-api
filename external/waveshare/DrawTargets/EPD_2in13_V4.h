#include <epaperapi.h>

namespace epaperapi {
namespace devices {
namespace EPD_2in13_V4 {
#include "../epaper/e-Paper/EPD_2in13_V4.h"

const int DEVICE_WIDTH = EPD_2in13_V4_WIDTH;
const int DEVICE_HEIGHT = EPD_2in13_V4_HEIGHT;

class EPD_2in13_DrawTarget : public AbstractDrawTarget {};

} // namespace EPD_2in13_V4
} // namespace devices
} // namespace epaperapi