//
// Created by MasterKtos on 14.12.2022.
//

#ifndef OPENGLGP_HOUSINGESTATE_GROUND_H
#define OPENGLGP_HOUSINGESTATE_GROUND_H

#include "ShapeHelpers.h"

namespace Shape {
    class Ground {
    public:
        static ShapeObject Get(int scale = 100, glm::vec3 color = glm::vec3(1, 1, 1)) {
            ShapeObject shape;
            shape.vertices.emplace_back(RenderBase::Vertex(glm::vec3(-1,0,-1)));   // BL
            shape.vertices.back().TexCoords = glm::vec2(0, 0);
            shape.vertices.emplace_back(RenderBase::Vertex(glm::vec3(1,0,-1)));   // BR
            shape.vertices.back().TexCoords = glm::vec2(scale, 0);
            shape.vertices.emplace_back(RenderBase::Vertex(glm::vec3(1,0,1)));   // FR
            shape.vertices.back().TexCoords = glm::vec2(scale, scale);
            shape.vertices.emplace_back(RenderBase::Vertex(glm::vec3(-1,0,1)));   // FL
            shape.vertices.back().TexCoords = glm::vec2(0, scale);
            for(auto &vertex : shape.vertices)
                vertex.Normal = color;
            shape.indices = {0, 1, 2,
                             2, 3, 0};
            return shape;
        }

        static ShapeObject GetWithNormals(int scale = 100) {
            auto shape = Get(scale);
            for(auto &vertex : shape.vertices)
                vertex.Normal = glm::vec3(0, 1, 0);
            return shape;
        }
    };
}

#endif //OPENGLGP_HOUSINGESTATE_GROUND_H
