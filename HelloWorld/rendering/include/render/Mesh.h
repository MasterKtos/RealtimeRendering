//
// Created by MasterKtos on 08.11.2022.
//

#ifndef OPENGLGP_MESH_H
#define OPENGLGP_MESH_H

#include "Renderable.h"
#include <vector>


namespace RenderBase {
    class Mesh : public Renderable {
    private:
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        unsigned int VBO, EBO;
    public:
        unsigned int VAO;

        Mesh(const std::vector<Vertex> &vertices,
             const std::vector<unsigned int> &indices);
        void Draw() override;
        void DrawInstanced(int amount) override;
    };

}


#endif //OPENGLGP_MESH_H
