Although the code in external/waveshare/epaper/e-Paper gives us the functions and tools to draw to their displays, annoyingly
it isn't namespaced out so we can only include one at a time.

As a workaround, we'll create files for each EPD device model as DrawTargets and using preprocessor directives, namespace
them there.
