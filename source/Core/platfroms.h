#pragma once

#include "Core/core.h"

#if defined(PLATFORM_ANDROID)
    #include <android/log.h>
    #include <jni.h>
#elif defined(PLATFORM_LINUX)
    #include <unistd.h>
    #include <X11/Xlib.h>
#elif defined(PLATFORM_WINDOWS)
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
#endif