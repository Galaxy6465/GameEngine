#pragma once

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>

namespace EngineLog {

enum class Level {
    Trace,
    Info,
    Warn,
    Error
};

inline constexpr std::string_view Reset = "\033[0m";

// Distinct 256-color shades so ENGINE and APP never look the same
namespace Palette {
    // Deep / dark shades (good for ENGINE)
    inline constexpr std::string_view DarkTeal   = "\033[38;5;24m";
    inline constexpr std::string_view DarkBlue   = "\033[38;5;27m";
    inline constexpr std::string_view DarkAmber  = "\033[38;5;130m";
    inline constexpr std::string_view DarkCrimson= "\033[38;5;124m";

    // Bright / light shades (good for APP)
    inline constexpr std::string_view LightMint  = "\033[38;5;121m";
    inline constexpr std::string_view LightSky   = "\033[38;5;117m";
    inline constexpr std::string_view LightGold  = "\033[38;5;221m";
    inline constexpr std::string_view LightCoral = "\033[38;5;210m";
}

inline std::string CurrentTime() {
    using clock = std::chrono::system_clock;
    const auto now = clock::now();
    const std::time_t tt = clock::to_time_t(now);

    std::tm tmBuf{};
#if defined(_WIN32)
    localtime_s(&tmBuf, &tt);
#else
    localtime_r(&tt, &tmBuf);
#endif

    std::ostringstream oss;
    oss << std::put_time(&tmBuf, "%H:%M:%S");
    return oss.str();
}

template <typename T>
inline decltype(auto) NormalizeArg(T&& arg) {
    using Decayed = std::decay_t<T>;
    if constexpr (std::is_same_v<Decayed, const char*> || std::is_same_v<Decayed, char*>) {
        return arg ? arg : "(null)";
    } else {
        return std::forward<T>(arg);
    }
}

template <typename... Args>
inline void Print(std::string_view prefix,
                  std::string_view lineColor,
                  Level level,
                  Args&&... args) {
    std::ostringstream msg;
    (msg << ... << NormalizeArg(std::forward<Args>(args)));

    std::string_view tag = "LOG";
    switch (level) {
        case Level::Trace: tag = "TRACE"; break;
        case Level::Info:  tag = "INFO";  break;
        case Level::Warn:  tag = "WARN";  break;
        case Level::Error: tag = "ERROR"; break;
    }

    std::ostream& out = (level == Level::Warn || level == Level::Error) ? std::cerr : std::cout;

    out << lineColor
        << "{" << CurrentTime() << "} [" << prefix << "::" << tag << "] " << msg.str()
        << Reset << '\n';
}

} // namespace EngineLog

// ENGINE -> Deep / dark shades (full line in one color)
#define ENGINE_TRACE(...) ::EngineLog::Print("ENGINE", ::EngineLog::Palette::DarkBlue,    ::EngineLog::Level::Trace, __VA_ARGS__)
#define ENGINE_INFO(...)  ::EngineLog::Print("ENGINE", ::EngineLog::Palette::DarkTeal,    ::EngineLog::Level::Info,  __VA_ARGS__)
#define ENGINE_WARN(...)  ::EngineLog::Print("ENGINE", ::EngineLog::Palette::DarkAmber,   ::EngineLog::Level::Warn,  __VA_ARGS__)
#define ENGINE_ERROR(...) ::EngineLog::Print("ENGINE", ::EngineLog::Palette::DarkCrimson, ::EngineLog::Level::Error, __VA_ARGS__)

// APP -> Bright / light shades (full line in one color)
#define APP_TRACE(...)    ::EngineLog::Print("APP",    ::EngineLog::Palette::LightSky,    ::EngineLog::Level::Trace, __VA_ARGS__)
#define APP_INFO(...)     ::EngineLog::Print("APP",    ::EngineLog::Palette::LightMint,   ::EngineLog::Level::Info,  __VA_ARGS__)
#define APP_WARN(...)     ::EngineLog::Print("APP",    ::EngineLog::Palette::LightGold,   ::EngineLog::Level::Warn,  __VA_ARGS__)
#define APP_ERROR(...)    ::EngineLog::Print("APP",    ::EngineLog::Palette::LightCoral,  ::EngineLog::Level::Error, __VA_ARGS__)