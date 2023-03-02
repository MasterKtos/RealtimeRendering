//
// Created by MasterKtos on 26.11.2022.
//

#ifndef OPENGLGP_IDISPLAYNODE_H
#define OPENGLGP_IDISPLAYNODE_H

#include "render/Shader.h"
#include "render/Texture.h"
#include <memory>
#include <utility>

class IDisplayNode {
public:
    std::shared_ptr<RenderBase::Shader> shader;
    std::shared_ptr<RenderBase::Texture> texture;

    IDisplayNode(std::shared_ptr<RenderBase::Shader> shader) :
        shader(std::move(shader)), texture(nullptr) {}

    virtual void Draw() {
        if(texture != nullptr) texture->bind();
    }
    virtual void LoadTexture(const std::string &path) {
        texture = std::make_shared<RenderBase::Texture>();
        texture->load(path);
    }
};

#endif //OPENGLGP_IDISPLAYNODE_H
