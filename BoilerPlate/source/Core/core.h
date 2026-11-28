#pragma once

// 1. Windows
#if defined(_WIN32) || defined(_WIN64)
    #define PLATFORM_WINDOWS
    #ifdef _WIN64
        #define PLATFORM_WINDOWS_64
    #else
        #define PLATFORM_WINDOWS_32
    #endif

// 2. Android (MUST come before __linux__)
#elif defined(__ANDROID__)
    #define PLATFORM_ANDROID

// 3. Linux
#elif defined(__linux__)
    #define PLATFORM_LINUX

// 4. Apple (macOS / iOS)
#elif defined(__APPLE__) || defined(__MACH__)
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR == 1 || TARGET_OS_IPHONE == 1
        #define PLATFORM_IOS
    #elif TARGET_OS_MAC == 1
        #define PLATFORM_MACOS
    #endif

// 5. Web (Emscripten)
#elif defined(__EMSCRIPTEN__)
    #define PLATFORM_WEB

#else
    #error "Unknown or unsupported platform!"
#endif


