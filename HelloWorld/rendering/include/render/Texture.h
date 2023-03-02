//
// Created by MasterKtos on 09.11.2022.
//

#ifndef OPENGLGP_TEXTURE_H
#define OPENGLGP_TEXTURE_H

#include <string>
#include "glad/glad.h"

namespace RenderBase {

    class Texture {
    public:
        GLuint to_id;
        bool use_linear;

        Texture();
        ~Texture();

        bool load(const std::string & file_name);

        void bind(int index = 0) const;
    };
}

#endif //OPENGLGP_TEXTURE_H
