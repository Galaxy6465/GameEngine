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
        // create objects
        APP_INFO("RenderLayer Attached!");
        
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

        shaderProgram = glCreateProgram();

        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);


        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Utils::Shader shader;
        // shader.LoadFromFiles("res/shaders/triangle.vs","res/shaders/triangle.fs");

    }

    void OnDetach() override
    {
        // delete objects
        APP_INFO("RenderLayer Detached!");
    }

    void OnUpdate() override {
        // update variables
    }

    void OnRender() override
    {
        // render objects
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        // glDrawArrays(GL_TRIANGLES, 0, 6);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glBindVertexArray(0);
    }

    float m_CubeColor[4] = {0.8f, 0.3f, 0.2f, 1.0f};

private:
    const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

    const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
    "}\n";


    unsigned int vertexShader;
    unsigned int fragmentShader;
    unsigned int shaderProgram;
    float vertices[15] = {
        -0.5f,  0.0f, 0.0f, 
        -0.25f, 0.5f, 0.0f, 

        0.0f, 0.0f, 0.0f, 

        0.25f,  0.5f, 0.0f,
        0.5f, 0.0f, 0.0f
    };
    unsigned int indices[6] = {  // note that we start from 0!
        0, 1, 2,   // first triangle
        2, 3, 4    // second triangle
    };
    unsigned int VAO, VBO, EBO;
};
