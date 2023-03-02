//
// Created by MasterKtos on 01.12.2022.
//

#include "include/render/lights/Light.h"

#include <utility>

RenderBase::Light::Light(std::string name, std::shared_ptr<Shader> shader,
                         std::shared_ptr<Shader> meshShader) :
        name(std::move(name)),
        lightShader(std::move(shader)),
        IDisplayNode(std::move(meshShader)),
        SceneNode(name) {
    ambient = glm::vec3(0.05f);
    diffuse = glm::vec3(0.8f);
    specular = glm::vec3(1.0f);
    color = glm::vec3(1.0f);

    SceneNode::Move(glm::vec3(0));
    SceneNode::Scale(glm::vec3(0.02f, 0.5f, 0.2f));
}

void RenderBase::Light::SetMesh(const Mesh &newMesh) {
    mesh = std::make_shared<Mesh>(newMesh);
}

void RenderBase::Light::Show() {
    IDisplayNode::Draw();
    glm::mat4 modelMat = GetTransform();

    shader->apply();
    shader->setMat4("model", modelMat);

    if(mesh != nullptr) mesh->Draw();

    lightShader->apply();

    lightShader->setVec3(name + ".color", color);
    lightShader->setVec3(name + ".position", transform.position);
    lightShader->setVec3(name + ".ambient", ambient);
    lightShader->setVec3(name + ".diffuse", diffuse);
    lightShader->setVec3(name + ".specular", specular);
}
