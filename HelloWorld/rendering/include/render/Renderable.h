//
// Created by MasterKtos on 15.11.2022.
//

#ifndef OPENGLGP_RENDERABLE_H
#define OPENGLGP_RENDERABLE_H

#include "glm/vec3.hpp"
#include "glm/vec2.hpp"

namespace RenderBase {
    struct Vertex
    {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;
        Vertex()
                : Position(glm::vec3(0)), Normal(glm::vec3(0)), TexCoords(glm::vec3(0)) {}
        Vertex(glm::vec3 pos, glm::vec3 norm, glm::vec2 texc)
                : Position(pos), Normal(norm), TexCoords(texc) {}
        Vertex(glm::vec3 pos)
                : Position(pos), Normal(glm::vec3(0)), TexCoords(glm::vec3(0)) {}
    };

    class Renderable {
    public:
        virtual void Draw() = 0;
        virtual void DrawInstanced(int amount) = 0;
    };
}

#endif //OPENGLGP_RENDERABLE_H
