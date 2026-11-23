#pragma once

#include "Layers/Layer.h"
#include "Core/Log.h"
#include "utils/u_camera.h"
#include "utils/u_shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

class MainRenderLayer : public Layer {
public:
    MainRenderLayer() : Layer("MainRenderLayer") {}

    void OnAttach() override
    {
        APP_INFO("RenderLayer Attached!");

        m_Shader.LoadFromFiles("res/cube.vs", "res/cube.fs");

        static const float cubeVertices[] = {
            // Front
            -0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f,  0.5f,
             0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f, -0.5f,  0.5f,
            // Back
             0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f, -0.5f,
            // Left
            -0.5f, -0.5f, -0.5f, -0.5f, -0.5f,  0.5f, -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f, -0.5f, -0.5f, -0.5f,
            // Right
             0.5f, -0.5f,  0.5f,  0.5f, -0.5f, -0.5f,  0.5f,  0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f,  0.5f, -0.5f,  0.5f,
            // Top
            -0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  0.5f, -0.5f,
             0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f,  0.5f,
            // Bottom
            -0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f, -0.5f
        };

        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        if (m_VAO == 0 || m_VBO == 0) {
            throw std::runtime_error("Failed to create cube vertex buffers");
        }

        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        glEnable(GL_DEPTH_TEST);
    }

    void OnDetach() override
    {
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
        m_VAO = 0;
        m_VBO = 0;
        m_Shader.Release();
        APP_INFO("RenderLayer Detached!");
    }

    void OnUpdate() override {}

    void OnRender() override
    {
        GLint viewport[4]{};
        glGetIntegerv(GL_VIEWPORT, viewport);
        if (viewport[2] <= 0 || viewport[3] <= 0) {
            return;
        }

        m_Camera.SetPerspective(
            Utils::DegreesToRadians(45.0f),
            static_cast<float>(viewport[2]) / static_cast<float>(viewport[3]),
            0.1f, 100.0f);

        const float time = static_cast<float>(glfwGetTime());
        const Utils::Mat4 model =
            Utils::Mat4::RotationY(time * 0.7f) *
            Utils::Mat4::RotationX(time * 0.35f);

        m_Shader.Use();
        m_Shader.SetMat4("u_Model", model);
        m_Shader.SetMat4("u_View", m_Camera.GetViewMatrix());
        m_Shader.SetMat4("u_Projection", m_Camera.GetProjectionMatrix());
        m_Shader.SetVec4(
            "u_Color",
            m_CubeColor[0], m_CubeColor[1], m_CubeColor[2], m_CubeColor[3]);

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glBindVertexArray(m_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    float m_CubeColor[4] = {0.8f, 0.3f, 0.2f, 1.0f};

private:
    Utils::Shader m_Shader;
    Utils::Camera m_Camera;
    GLuint m_VAO = 0;
    GLuint m_VBO = 0;
};
