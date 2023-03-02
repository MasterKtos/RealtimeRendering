//
// Created by MasterKtos on 26.11.2022.
//

#include "HousingEstate/SceneObject.h"

#include <utility>

SceneObject::SceneObject(std::shared_ptr<RenderBase::Shader> shader, std::string nodeName)
            : IDisplayNode(std::move(shader)), SceneNode(std::move(nodeName)) {}

void SceneObject::SetMesh(const RenderBase::Mesh &newMesh) {
    if(mesh != nullptr) mesh.reset();
    mesh = std::make_shared<RenderBase::Mesh>(newMesh);
}

void SceneObject::Draw() {
    glm::mat4 modelMat = GetTransform();

    shader->apply();
    shader->setMat4("model", modelMat);

    IDisplayNode::Draw();

    if(mesh != nullptr) {
        mesh->Draw();
    }
}
