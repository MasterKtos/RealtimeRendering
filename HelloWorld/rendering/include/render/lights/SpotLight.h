//
// Created by MasterKtos on 12.12.2022.
//

#ifndef OPENGLGP_HOUSINGESTATE_SPOTLIGHT_H
#define OPENGLGP_HOUSINGESTATE_SPOTLIGHT_H

#include "Light.h"

namespace RenderBase {
    class SpotLight : public Light {
    protected:

    public:
        float constant;
        float linear;
        float quadratic;

        float cutOff;
        float outerCutOff;

        SpotLight(const std::string &name,
                  const std::shared_ptr<Shader> &shader,
                  const std::shared_ptr<Shader> &meshShader);

        void Show() override;
    };
}

#endif //OPENGLGP_HOUSINGESTATE_SPOTLIGHT_H
