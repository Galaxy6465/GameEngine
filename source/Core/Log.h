#pragma once
#include <iostream>

// ANSI Color Codes
#define LOG_COLOR_RESET   "\033[0m"
#define LOG_COLOR_TRACE   "\033[37m" // Light Gray / White
#define LOG_COLOR_INFO    "\033[32m" // Green
#define LOG_COLOR_WARN    "\033[33m" // Yellow
#define LOG_COLOR_ERROR   "\033[31m" // Red

template <typename... Args>
inline void LogPrint(const char* color, const char* prefix, Args&&... args) {
    std::cout << color << prefix;
    ((std::cout << args), ...);
    std::cout << LOG_COLOR_RESET << std::endl;
}

// Application Logs
#define APP_INFO(...)     LogPrint(LOG_COLOR_INFO,  "APP::INFO: ",  __VA_ARGS__)
#define APP_TRACE(...)    LogPrint(LOG_COLOR_TRACE, "APP::TRACE: ", __VA_ARGS__)
#define APP_ERROR(...)    LogPrint(LOG_COLOR_ERROR, "APP::ERROR: ", __VA_ARGS__)
#define APP_WARN(...)     LogPrint(LOG_COLOR_WARN,  "APP::WARN: ",  __VA_ARGS__)

// Window Logs
#define WIN_INFO(...)     LogPrint(LOG_COLOR_INFO,  "WINDOW::INFO: ",  __VA_ARGS__)
#define WIN_TRACE(...)    LogPrint(LOG_COLOR_TRACE, "WINDOW::TRACE: ", __VA_ARGS__)
#define WIN_ERROR(...)    LogPrint(LOG_COLOR_ERROR, "WINDOW::ERROR: ", __VA_ARGS__)
#define WIN_WARN(...)     LogPrint(LOG_COLOR_WARN,  "WINDOW::WARN: ",  __VA_ARGS__)

// Layer Logs
#define LAYER_INFO(...)   LogPrint(LOG_COLOR_INFO,  "LAYER::INFO: ",  __VA_ARGS__)
#define LAYER_TRACE(...)  LogPrint(LOG_COLOR_TRACE, "LAYER::TRACE: ", __VA_ARGS__)
#define LAYER_ERROR(...)  LogPrint(LOG_COLOR_ERROR, "LAYER::ERROR: ", __VA_ARGS__)
#define LAYER_WARN(...)   LogPrint(LOG_COLOR_WARN,  "LAYER::WARN: ",  __VA_ARGS__)


#if defined(PLATFORM_ANDROID)
    #include <android/log.h>
    #include <sstream>

    template <typename... Args>
    inline void LogPrintAndroid(int prio, const char* tag, Args&&... args) {
        std::ostringstream oss;
        ((oss << args), ...);
        __android_log_print(prio, tag, "%s", oss.str().c_str());
    }

    #define APP_INFO(...)  LogPrintAndroid(ANDROID_LOG_INFO,  "APP", __VA_ARGS__)
    #define APP_WARN(...)  LogPrintAndroid(ANDROID_LOG_WARN,  "APP", __VA_ARGS__)
    #define APP_ERROR(...) LogPrintAndroid(ANDROID_LOG_ERROR, "APP", __VA_ARGS__)
#endif
