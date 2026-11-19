#include "window/Window.h"
#include "Mesh/Object.h"

class MainWindow : public Window {
public:
    MainWindow(const char* title, float width, float height);

    void Init_OpenGL();

    void OnUpdate() override;

    void Clean();

    void CreateWindow() override;
public:
    Object Triangle;
};