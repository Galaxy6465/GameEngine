#pragma once

namespace Specifications {

    struct ApplicationContext {
        const char* app_Name = "Placeholder";
        bool app_VSync = false;
        float app_Width = 1280;
        float app_Height = 720;
    };

    inline static ApplicationContext appSpecifiactions;

    struct WindowContext {
        const char* win_Name = "Default Window";
        float win_Width = 800;
        float win_Height = 600;
    };

    // use global winRegistry (remember)

};

