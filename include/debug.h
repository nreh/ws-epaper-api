#include <string>

#define WSEPAPERAPI_DEBUG_MODE // enable debug logging

namespace epaperapi {
namespace debug {
void DebugLog(std::string message);

#ifdef WSEPAPERAPI_DEBUG_MODE
    #define DEBUG(x) epaperapi::debug::DebugLog(#x)
#else
    #define DEBUG(x)
#endif

} // namespace debug
} // namespace epaperapi