#include <iostream>

#include "Core/Log.h"
#include "Application/Application.h"

int main() {
    
    int returnCode = 0;
    
    APP_INFO(" INITIALIZING..::", "Galaxy Engine");
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