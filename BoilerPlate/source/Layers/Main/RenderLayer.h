#pragma once

// App Includes
#include "Layers/Layer.h"
#include "Core/Log.h"
#include "Core/Settings.h"

// Utils
#include "utils/u_shader.h"
#include "utils/u_camera.h"
#include "utils/u_texture.h"
#include "utils/stb_image.h"

// GLFW / GLAD
#include "imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// C++ Library
#include <optional>

class MainRenderLayer : public Layer {
public:
    MainRenderLayer() : Layer("MainRenderLayer") {}

    void OnAttach() override {
        APP_INFO("RenderLayer Attached!");

        m_Shader.emplace("res/shaders/triangle.vs", "res/shaders/triangle.fs");

        //* Start ---------------------------------->
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        glGenBuffers(1, &m_EBO);

        glBindVertexArray(m_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(m_Vertices), m_Vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_Indices), m_Indices, GL_STATIC_DRAW);

        constexpr GLsizei stride = 8 * sizeof(float);
        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(0));
        glEnableVertexAttribArray(0);
        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        // texture coord attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
        //* End --------------------------------------->

        m_Texture = loadTexture("res/textures/container.jpg");

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void OnDetach() override {
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
        glDeleteBuffers(1, &m_EBO);
        glDeleteTextures(1, &m_Texture);
        m_Shader.reset();

        APP_INFO("RenderLayer Detached!");
    }

    void OnUpdate() override {
        // update variables
    }

    void OnRender() override {
        const auto& bg = Settings::wind_Settings[0].backgroundColor;
        glClearColor(bg.col[0], bg.col[1], bg.col[2], bg.alpha);
        glClear(GL_COLOR_BUFFER_BIT);

        if (!m_Shader.has_value()) {
            return;
        }
        

        float t = (float)glfwGetTime() * 5;
        // t = 1;
        m_Shader->setFloat("x", t);
        m_Shader->setFloat("y", t);
m_Shader->use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_Texture);
        glBindVertexArray(m_VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

private:
    float m_Vertices[32] = {
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f
    };

    unsigned int m_Indices[6] = {
        0, 1, 3,
        1, 2, 3
    };

    unsigned int m_VAO = 0, m_VBO = 0, m_EBO = 0;
    unsigned int m_Texture = 0;
    std::optional<Shader> m_Shader;
};