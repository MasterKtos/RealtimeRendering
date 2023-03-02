//
// Created by MasterKtos on 12.12.2022.
//

#ifndef OPENGLGP_HOUSINGESTATE_POINTLIGHT_H
#define OPENGLGP_HOUSINGESTATE_POINTLIGHT_H

#include "Light.h"

namespace RenderBase {
    class PointLight : public Light{
    protected:

    public:
        float constant;
        float linear;
        float quadratic;

        PointLight(const std::string &name,
                   const std::shared_ptr<Shader> &shader,
                   const std::shared_ptr<Shader> &meshShader);

        void Show() override;
    };
}

#endif //OPENGLGP_HOUSINGESTATE_POINTLIGHT_H
