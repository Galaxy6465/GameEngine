#ifndef INPUT_HPP
#define INPUT_HPP

#include "camera.h"
#include <GLFW/glfw3.h>

class Inputs {
public:
    static void InitCallBacks(GLFWwindow* window, Camera &m_camera);
    static void ProcessInput(GLFWwindow* window, float deltaTime);

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};

#endif