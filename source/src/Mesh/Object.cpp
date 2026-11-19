#include "Mesh/Object.h"

Object::~Object()
{
    delete shader;
    delete texture;
    
    if (m_data.VAO) glDeleteVertexArrays(1, &m_data.VAO);
    if (m_data.VBO) glDeleteBuffers(1, &m_data.VBO);
    if (m_data.EBO) glDeleteBuffers(1, &m_data.EBO);
}

void Object::Init()
{
    glGenVertexArrays(1, &m_data.VAO);
    glGenBuffers(1, &m_data.VBO);
    glGenBuffers(1, &m_data.EBO);

    glBindVertexArray(m_data.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_data.VBO);
    glBufferData(GL_ARRAY_BUFFER, m_data.vertices.size() * sizeof(Vertex), m_data.vertices.data(), GL_STATIC_DRAW);

    if (!m_data.indices.empty())
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_data.EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_data.indices.size() * sizeof(unsigned int), m_data.indices.data(), GL_STATIC_DRAW);
    }

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

    glBindVertexArray(0);
}

void Object::Draw()
{
    if (shader)
        shader->use();

    if (texture)
        texture->Bind(0);

    glBindVertexArray(m_data.VAO);

    if (!m_data.indices.empty())
    {
        glDrawElements(
            GL_TRIANGLES,
            static_cast<GLsizei>(m_data.indices.size()),
            GL_UNSIGNED_INT, 
            nullptr
        );
    }
    else
    {
        glDrawArrays(
            GL_TRIANGLES,
            0,
            static_cast<GLsizei>(m_data.vertices.size())
        );
    }

    glBindVertexArray(0);
}

void Object::SetShader(std::string vs, std::string fs)
{
    delete shader;
    shader = new Shader(vs.c_str(), fs.c_str());
}

void Object::SetTextures(std::string texPath)
{
    delete texture;
    texture = new Texture(texPath.c_str());
}