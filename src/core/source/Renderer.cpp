#include "Renderer.h"
#include <glm/gtc/matrix_transform.hpp>

Renderer::Renderer(const glm::mat4& view, const glm::mat4& projection)
    : view(view), projection(projection) {
}

void Renderer::Draw(const ObjectData& object, const ObjectValues& objectValues, const int count) {
    object.shader->setMat4("view", view);
    object.shader->setMat4("projection", projection);

    // Apply position and size from objectValues
    glm::mat4 objectModel = glm::mat4(1.0f);
    objectModel = glm::translate(objectModel, objectValues.position);
    objectModel = glm::scale(objectModel, objectValues.size);
    object.shader->setMat4("model", objectModel);

    // Apply color & texture
    object.shader->setVec3("objectColor", objectValues.color);
    if (object.texture != nullptr) {
        object.texture->Bind(0);
        object.shader->setBool("textures", true);
        object.shader->setInt("ourTexture", 0);
    } else {
        object.shader->setBool("textures", false);
    }

    glBindVertexArray(object.VAO);
    glDrawArrays(GL_TRIANGLES, 0, count);
    glBindVertexArray(0);
}
