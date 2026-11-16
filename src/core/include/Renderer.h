#pragma once
#include "ObjectStructure.h"

class Renderer {
public:
    Renderer(const glm::mat4& view, const glm::mat4& projection);
    ~Renderer() = default;

    // Pass any object you want to draw here!
    void Draw(const ObjectData& object, const ObjectValues& objectValues = ObjectValues{}, const int count = 0);

private:
    const glm::mat4& view;
    const glm::mat4& projection;
};
