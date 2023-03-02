//
// Created by MasterKtos on 09.11.2022.
//

#ifndef OPENGLGP_MODEL_H
#define OPENGLGP_MODEL_H

#include <string>
#include "Mesh.h"
#include "assimp/scene.h"
#include "Renderable.h"

namespace RenderBase {

    class Model : public Renderable {
    private:
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    public:
        std::vector<Mesh> meshes;
        std::string directory;

        Model(std::string const &path);
        void Draw() override;
        void DrawInstanced(int amount) override;
    };
}

#endif //OPENGLGP_MODEL_H
