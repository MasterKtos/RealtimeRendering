//
// Created by MasterKtos on 26.11.2022.
//

#ifndef OPENGLGP_ROOF_H
#define OPENGLGP_ROOF_H

#include "ShapeHelpers.h"

namespace Shape {
    class Roof {
    public:
        static ShapeObject Get(glm::vec3 color = glm::vec3(1, 1, 1)) {
            ShapeObject shape;
            shape.vertices.emplace_back(glm::vec3( -1, -1, -1)); // BL 0
            shape.vertices.back().TexCoords = glm::vec2(0, 0);
            shape.vertices.emplace_back(glm::vec3(  1, -1, -1)); // BR 1
            shape.vertices.back().TexCoords = glm::vec2(1, 0);
            shape.vertices.emplace_back(glm::vec3(  1, -1,  1)); // FR 2
            shape.vertices.back().TexCoords = glm::vec2(1, 1);
            shape.vertices.emplace_back(glm::vec3( -1, -1,  1)); // FL 3
            shape.vertices.back().TexCoords = glm::vec2(0, 1);
            shape.vertices.emplace_back(glm::vec3(  0,  1,  0)); // U  4
            shape.vertices.back().TexCoords = glm::vec2(0.5f, 0.5f);
            for(auto &vertex : shape.vertices)
                vertex.Normal = color;
            shape.indices = {0, 1, 4,
                             1, 2, 4,
                             2, 3, 4,
                             3, 0, 4};
            return shape;
        }
        static ShapeObject GetWithNormals() {
            auto vertices = Get().vertices;
            ShapeObject shape;
            // Back face
            glm::vec3 backNormal(0, 1, -1);
            backNormal = glm::normalize(backNormal);
            shape.vertices.push_back(vertices[0]);
            shape.vertices.back().Normal = backNormal;
            shape.vertices.push_back(vertices[1]);
            shape.vertices.back().Normal = backNormal;
            shape.vertices.push_back(vertices[4]);
            shape.vertices.back().Normal = backNormal;
            // Left face
            glm::vec3 leftNormal(-1, 1, 0);
            leftNormal = glm::normalize(leftNormal);
            shape.vertices.push_back(vertices[0]);
            shape.vertices.back().Normal = leftNormal;
            shape.vertices.push_back(vertices[3]);
            shape.vertices.back().Normal = leftNormal;
            shape.vertices.push_back(vertices[4]);
            shape.vertices.back().Normal = glm::vec3();
            // Front face
            glm::vec3 frontNormal(0, 1, 1);
            shape.vertices.push_back(vertices[2]);
            shape.vertices.back().Normal = frontNormal;
            shape.vertices.push_back(vertices[3]);
            shape.vertices.back().Normal = frontNormal;
            shape.vertices.push_back(vertices[4]);
            shape.vertices.back().Normal = frontNormal;
            // Right face
            glm::vec3 rightNormal(1, 1, 0);
            shape.vertices.push_back(vertices[1]);
            shape.vertices.back().Normal = rightNormal;
            shape.vertices.push_back(vertices[2]);
            shape.vertices.back().Normal = rightNormal;
            shape.vertices.push_back(vertices[4]);
            shape.vertices.back().Normal = rightNormal;

            shape.indices = {
                    0, 1, 2,
                    3, 4, 5,
                    6, 7, 8,
                    9, 10, 11
            };
            return shape;
        }
    };
}

#endif //OPENGLGP_ROOF_H
