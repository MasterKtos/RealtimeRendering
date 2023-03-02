//
// Created by MasterKtos on 12.12.2022.
//

#include "include/render/lights/DirectionalLight.h"
#include "glm/trigonometric.hpp"

RenderBase::DirectionalLight::DirectionalLight(const std::string &name,
                                               const std::shared_ptr<Shader> &shader,
                                               const std::shared_ptr<Shader> &meshShader) :
                                               Light(name, shader, meshShader) {
    SceneNode::Move(glm::vec3(0, 5.0f, 0));
    SceneNode::Rotate(glm::vec3(-0.2f*360, -1.0f*360, -0.3f*360));

    ambient = glm::vec3(0.05f);
    diffuse = glm::vec3(0.8f);
    specular = glm::vec3(1.0f);
}

void RenderBase::DirectionalLight::Show() {
    Light::Show();

    lightShader->setVec3(name + ".direction", glm::radians(transform.rotation));
}
