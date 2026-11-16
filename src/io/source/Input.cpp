#include "Input.h"

static float lastX = 400.0f;
static float lastY = 400.0f;
static bool firstMouse = true;

// Static pointer to hold the reference passed from Init()
static Camera* s_Camera = nullptr;
static float dt;
static bool mouseEnable;

bool qKeyWasPressed = false; 
void TriggerMouse (GLFWwindow* window) {
    // Read the current instantaneous state of the Q key
    bool qKeyPressedNow = (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS);
    // Trigger ONLY on the exact frame the key transitions from unpressed to pressed
    if (qKeyPressedNow && !qKeyWasPressed)
    {
        mouseEnable = !mouseEnable;
        if (mouseEnable)
        {
            // Free the cursor for UI/Menu navigation
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        else
        {
            // Lock cursor down for boundless 3D camera controls
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            
            // Prime your mouse callback to completely ignore the entry frame jump
            firstMouse = true; 
        }
    }
    
    // Save current frame's key state for the next frame's comparison
    qKeyWasPressed = qKeyPressedNow;
}

void TriggerPush() {
    
}

void Inputs::InitCallBacks(GLFWwindow* window, Camera &m_camera){
    s_Camera = &m_camera; // Store the address of context.camera
    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, Inputs::framebuffer_size_callback);
    glfwSetCursorPosCallback(window, Inputs::mouse_callback);
    glfwSetScrollCallback(window, Inputs::scroll_callback); // Now matches GLFWscrollfun perfectly!

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Inputs::ProcessInput(GLFWwindow* window, float deltaTime) {

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if(s_Camera->Position.y < 1){
        s_Camera->Position.y = 1;
    }

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        s_Camera->ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        s_Camera->ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        s_Camera->ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        s_Camera->ProcessKeyboard(RIGHT, deltaTime);
    
    TriggerMouse(window);
}

void Inputs::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// Exactly matches GLFWcursorposfun signature
void Inputs::mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    if (mouseEnable)
    {
        return;
    }

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 

    lastX = xpos;
    lastY = ypos;

    s_Camera->ProcessMouseMovement(xoffset, yoffset);
}

// Exactly matches GLFWscrollfun signature
void Inputs::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    if (!s_Camera) return;

    s_Camera->ProcessMouseScroll(static_cast<float>(yoffset));
}