//
// Created by MasterKtos on 26.11.2022.
//

#ifndef OPENGLGP_HOUSE_H
#define OPENGLGP_HOUSE_H

#include "ShapeHelpers.h"

namespace Shape {
    class House {
    public:
        static ShapeObject Get(glm::vec3 color = glm::vec3(1, 1, 1)) {
            ShapeObject shape;
            // Down
            shape.vertices.emplace_back(RenderBase::Vertex(glm::vec3(-1,-1,-1)));   // DBL
            shape.vertices.back().TexCoords = glm::vec2(1, 1);
            shape.vertices.emplace_back(RenderBase::Vertex(glm::vec3( 1,-1,-1)));   // DBR
            shape.vertices.back().TexCoords = glm::vec2(0, 1);
            shape.vertices.emplace_back(RenderBase::Vertex(glm::vec3( 1,-1, 1)));   // DFR
            shape.vertices.back().TexCoords = glm::vec2(1, 1);
            shape.vertices.emplace_back(RenderBase::Vertex(glm::vec3(-1,-1, 1)));   // DFL
            shape.vertices.back().TexCoords = glm::vec2(0, 1);
            // Up
            shape.vertices.emplace_back(RenderBase::Vertex(glm::vec3(-1, 1,-1)));   // UBL
            shape.vertices.back().TexCoords = glm::vec2(1, 0);
            shape.vertices.emplace_back(RenderBase::Vertex(glm::vec3( 1, 1,-1)));   // UBR
            shape.vertices.back().TexCoords = glm::vec2(0, 0);
            shape.vertices.emplace_back(RenderBase::Vertex(glm::vec3( 1, 1, 1)));   // UFR
            shape.vertices.back().TexCoords = glm::vec2(1, 0);
            shape.vertices.emplace_back(RenderBase::Vertex(glm::vec3(-1, 1, 1)));   // UFL
            shape.vertices.back().TexCoords = glm::vec2(0, 0);
            for(auto &vertex : shape.vertices)
                vertex.Normal = color;
            shape.indices = {0, 1, 4,
                             1, 5, 4,
                             1, 2, 5,
                             2, 5, 6,
                             2, 3, 6,
                             3, 6, 7,
                             0, 3, 4,
                             3, 4, 7,
                             4, 5, 6,
                             4, 6, 7};
            return shape;
        }

        static ShapeObject GetWithNormals() {
            auto vertices = Get().vertices;
            ShapeObject shape;
            // Back face
            glm::vec3 backNormal(0, 0, -1);
            shape.vertices.push_back(vertices[0]);
            shape.vertices.back().Normal = backNormal;
            shape.vertices.push_back(vertices[1]);
            shape.vertices.back().Normal = backNormal;
            shape.vertices.push_back(vertices[4]);
            shape.vertices.back().Normal = backNormal;
            shape.vertices.push_back(vertices[5]);
            shape.vertices.back().Normal = backNormal;
            //Right face
            glm::vec3 rightNormal(1, 0, 0);
            shape.vertices.push_back(vertices[1]);
            shape.vertices.back().Normal = rightNormal;
            shape.vertices.push_back(vertices[2]);
            shape.vertices.back().Normal = rightNormal;
            shape.vertices.push_back(vertices[5]);
            shape.vertices.back().Normal = rightNormal;
            shape.vertices.push_back(vertices[6]);
            shape.vertices.back().Normal = rightNormal;
            // Front face
            glm::vec3 frontNormal = -backNormal;
            shape.vertices.push_back(vertices[2]);
            shape.vertices.back().Normal = frontNormal;
            shape.vertices.push_back(vertices[3]);
            shape.vertices.back().Normal = frontNormal;
            shape.vertices.push_back(vertices[6]);
            shape.vertices.back().Normal = frontNormal;
            shape.vertices.push_back(vertices[7]);
            shape.vertices.back().Normal = frontNormal;
            // Left face
            glm::vec3 leftNormal = -rightNormal;
            shape.vertices.push_back(vertices[0]);
            shape.vertices.back().Normal = leftNormal;
            shape.vertices.push_back(vertices[3]);
            shape.vertices.back().Normal = leftNormal;
            shape.vertices.push_back(vertices[4]);
            shape.vertices.back().Normal = leftNormal;
            shape.vertices.push_back(vertices[7]);
            shape.vertices.back().Normal = leftNormal;

            shape.indices = {0, 1, 2,
                             1, 2, 3,

                             4, 5, 6,
                             5, 6, 7,

                             8, 9, 10,
                             9, 10, 11,

                             12, 13, 14,
                             13, 14, 15};
            return shape;
        }
    };
}

#endif //OPENGLGP_HOUSE_H
