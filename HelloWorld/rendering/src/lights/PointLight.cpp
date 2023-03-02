//
// Created by MasterKtos on 12.12.2022.
//

#include "include/render/lights/PointLight.h"

RenderBase::PointLight::PointLight(const std::string &name,
                                   const std::shared_ptr<Shader> &shader,
                                   const std::shared_ptr<Shader> &meshShader) :
                                   Light(name, shader, meshShader) {

    ambient = glm::vec3(0.05f);
    diffuse = glm::vec3(0.8f);
    specular = glm::vec3(1.0f);

    constant = 1.0f;
    linear = 0.09f;
    quadratic = 0.032f;
}

void RenderBase::PointLight::Show() {
    Light::Show();

    lightShader->setFloat(name + ".constant", constant);
    lightShader->setFloat(name + ".linear", linear);
    lightShader->setFloat(name + ".quadratic", quadratic);
}
