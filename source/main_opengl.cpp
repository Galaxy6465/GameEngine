#include <iostream>

#include "Core/Log.h"
#include "Application/Application.h"

#include "Application/ApplicationContext.h"

int main() {
    int returnCode = 0;
    Specifications::appSpecifiactions.app_Name = "Galaxy Engine";
    Specifications::appSpecifiactions.app_Width = 1280;
    Specifications::appSpecifiactions.app_Height = 720;
    Specifications::appSpecifiactions.app_VSync = false;
    
    APP_INFO(" INITIALIZING..::", Specifications::appSpecifiactions.app_Name);
    Application app;
    returnCode =  app.Init();
    APP_INFO("INITIALIZED::SUCCESSFULLY");

    APP_INFO("STARTING...");
    if(returnCode >= 0)
    {
        app.Run();
    }
    app.Clean();
    APP_TRACE("CLOSED::" , "WITH CODE::", returnCode);
    return 0;
}