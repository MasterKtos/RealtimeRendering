//
// Created by MasterKtos on 01.12.2022.
//

#ifndef OPENGLGP_HOUSINGESTATE_LIGHT_H
#define OPENGLGP_HOUSINGESTATE_LIGHT_H

#include <memory>
#include "glm/vec3.hpp"
#include "render/Shader.h"
#include "render/Mesh.h"
#include "../../../src/HousingEstate/SceneObject.h"

namespace RenderBase {
    class Light : public SceneNode, public IDisplayNode {
    protected:
        std::shared_ptr<Shader> lightShader;
        std::shared_ptr<Mesh> mesh;
        std::string name;
    public:
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
        glm::vec3 color;


        Light(std::string name, std::shared_ptr<Shader> shader,
              std::shared_ptr<Shader> meshShader);
        void SetMesh(const Mesh &newMesh);

        virtual void Show();
    };
}


#endif //OPENGLGP_HOUSINGESTATE_LIGHT_H
