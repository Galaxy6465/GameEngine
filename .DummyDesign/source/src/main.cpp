#include <GalaxyEngine.h>

extern GalaxyEngine::Application* GalaxyEngine::CreateApplication();

//! ------------ ENTRY POINT -------------------
int main() {
    auto app = GalaxyEngine::CreateApplication();
    app->Run();
    delete app;
}
//! --------------------------------------------