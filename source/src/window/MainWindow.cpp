#include "window/MainWindow.h"
#include "Debug/Debug.h"
#include "utils/shader_m.h"

MainWindow::MainWindow(const char* title, float width, float height)
    : Window(title, width, height){}

void MainWindow::OnUpdate()
{
    Triangle.Draw();
    APP_TRACE("Updating Window : ", win_ctx.title);
}

void MainWindow::CreateWindow()
{
    APP_INFO("Window overrided :", win_ctx.title);

}

void MainWindow::Init_OpenGL()
{
    ObjectData& data = Triangle.GetObjectData();

    data.vertices = {
        Vertex{ glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f) },
        Vertex{ glm::vec3( 0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f) },
        Vertex{ glm::vec3( 0.0f,  0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.5f, 1.0f) }
    };

    data.indices = { 0, 1, 2 };

    Triangle.SetShader("resources/shaders/triangle.vs", "resources/shaders/triangle.fs");
    Triangle.SetTextures("resources/textures/container.jpg");

    Triangle.Init();
}

void MainWindow::Clean()
{
}