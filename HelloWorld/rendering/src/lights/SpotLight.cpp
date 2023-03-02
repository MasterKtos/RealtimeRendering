//
// Created by MasterKtos on 12.12.2022.
//

#include <cmath>
#include "include/render/lights/SpotLight.h"
#include "glm/trigonometric.hpp"

RenderBase::SpotLight::SpotLight(const std::string &name,
                                 const std::shared_ptr<Shader> &shader,
                                 const std::shared_ptr<Shader> &meshShader) :
                                 Light(name, shader, meshShader) {
    Rotate(glm::vec3(1, 0, 0));

    ambient = glm::vec3(0);
    diffuse = glm::vec3(1.0f);
    specular = glm::vec3(1.0f);

    constant = 1.0f;
    linear = 0.09f;
    quadratic = 0.032f;

    cutOff = glm::cos(glm::radians(12.5f));
    outerCutOff = glm::cos(glm::radians(15.0f));
}

void RenderBase::SpotLight::Show() {
    Light::Show();

    lightShader->setVec3(name + ".direction", glm::radians(transform.rotation));

    lightShader->setFloat(name + ".constant", constant);
    lightShader->setFloat(name + ".linear", linear);
    lightShader->setFloat(name + ".quadratic", quadratic);

    lightShader->setFloat(name + ".cutOff", cutOff);
    lightShader->setFloat(name + ".outerCutOff", outerCutOff);
}
