//
// Created by MasterKtos on 12.12.2022.
//

#ifndef OPENGLGP_HOUSINGESTATE_DIRECTIONALLIGHT_H
#define OPENGLGP_HOUSINGESTATE_DIRECTIONALLIGHT_H

#include "Light.h"

namespace RenderBase {
    class DirectionalLight : public Light {
    public:
        DirectionalLight(const std::string &name, const std::shared_ptr<Shader> &shader,
                         const std::shared_ptr<Shader> &meshShader);

        void Show() override;
    };
}

#endif //OPENGLGP_HOUSINGESTATE_DIRECTIONALLIGHT_H
