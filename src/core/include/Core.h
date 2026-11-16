#pragma once

// ==========================================================================
// Platform Detection
// ==========================================================================

#if defined(_WIN32) || defined(_WIN64)
    #define AETHER_PLATFORM_WINDOWS
    #ifdef _WIN64
        #define AETHER_PLATFORM_WIN64
    #else
        #define AETHER_PLATFORM_WIN32
        #error "32-bit Windows builds are not supported by Aether Engine!"
    #endif
#elif defined(__APPLE__) || defined(__MACH__)
    #define AETHER_PLATFORM_MACOS
    #include <TargetConditionals.h>
    #if TARGET_OS_IPHONE
        #define AETHER_PLATFORM_IOS
        #error "iOS is not supported!"
    #endif
#elif defined(__linux__) || defined(__gnu_linux__)
    #define AETHER_PLATFORM_LINUX
#elif defined(__ANDROID__)
    #define AETHER_PLATFORM_ANDROID
    #error "Android is not supported!"
#elif defined(__unix__)
    #define AETHER_PLATFORM_UNIX
#else
    #error "Unknown or unsupported operating system platform!"
#endif

// ==========================================================================
// DLL Export / Import Setup (For Windows / Shared Libraries)
// ==========================================================================
#ifdef AETHER_PLATFORM_WINDOWS
    #ifdef AETHER_BUILD_DLL
        #define AETHER_API __declspec(dllexport)
    #else
        #define AETHER_API __declspec(dllimport)
    #endif
#else
    #define AETHER_API
#endif

// ==========================================================================
// Utility Macros
// ==========================================================================
#define BIT(x) (1 << (x))

// Assertion and Debug macros
#ifdef AETHER_DEBUG
    #if defined(AETHER_PLATFORM_WINDOWS)
        #define AETHER_DEBUGBREAK() __debugbreak()
    #elif defined(AETHER_PLATFORM_LINUX) || defined(AETHER_PLATFORM_MACOS)
        #include <signal.h>
        #define AETHER_DEBUGBREAK() raise(SIGTRAP)
    #else
        #define AETHER_DEBUGBREAK()
    #endif

    #define AETHER_ENABLE_ASSERTS
#else
    #define AETHER_DEBUGBREAK()
#endif

#ifdef AETHER_ENABLE_ASSERTS
    #define AETHER_ASSERT(x, ...) { if(!(x)) { std::cerr << "Assertion Failed: " << __VA_ARGS__ << std::endl; AETHER_DEBUGBREAK(); } }
    #define AETHER_CORE_ASSERT(x, ...) { if(!(x)) { std::cerr << "Core Assertion Failed: " << __VA_ARGS__ << std::endl; AETHER_DEBUGBREAK(); } }
#else
    #define AETHER_ASSERT(x, ...)
    #define AETHER_CORE_ASSERT(x, ...)
#endif