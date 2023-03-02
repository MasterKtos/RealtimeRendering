//
// Created by MasterKtos on 26.11.2022.
//

#ifndef OPENGLGP_SCENEOBJECT_H
#define OPENGLGP_SCENEOBJECT_H

#include <memory>
#include "render/Mesh.h"
#include "glm/ext/matrix_float4x4.hpp"
#include "render/Shader.h"
#include "SceneNode.h"
#include "IDisplayNode.h"

class SceneObject : public SceneNode, public IDisplayNode {
private:
    std::shared_ptr<RenderBase::Mesh> mesh;
public:
    SceneObject(std::shared_ptr<RenderBase::Shader> shader, std::string nodeName);

    void SetMesh(const RenderBase::Mesh &newMesh);

    void Draw() override;
};


#endif //OPENGLGP_SCENEOBJECT_H
