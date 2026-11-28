#pragma once

struct Color {
    float col[3];
    float alpha;
};

namespace Settings {

    //X App Settings
    static bool VSync;
    static Color AppColor;
    static bool ThemeDark;


    //X Window Settings
    struct WindowSettigns {
        const char* winName;
        Color backgroundColor;
    };
    inline static std::vector<WindowSettigns> wind_Settings = {
        {.winName = "Main", .backgroundColor = {  {0.15f, 0.15f, 0.18f}, 1.0f}}
    };
    
};