#include <string>

#define WSEPAPERAPI_DEBUG_MODE // enable debug logging

namespace epaperapi {
namespace debug {
void DebugLog(std::string message);

#ifdef WSEPAPERAPI_DEBUG_MODE
    #define WSAPI_DEBUG(x) epaperapi::debug::DebugLog(#x)
#else
    #define WSAPI_DEBUG(x)
#endif

} // namespace debug
} // namespace epaperapi