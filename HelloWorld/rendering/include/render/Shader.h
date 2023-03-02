//
// Created by MasterKtos on 09.11.2022.
//

#ifndef OPENGLGP_SHADER_H
#define OPENGLGP_SHADER_H

#include <string>
#include <map>
#include <functional>
#include "glad/glad.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/fwd.hpp"

namespace RenderBase {

    class Shader {
    private:
        bool isLinked;

        bool link();
        std::string loadFile(const std::string & filename);

    public:
        GLuint programID;


        Shader(const std::string & vertexShaderFilename,
                     const std::string & fragmentShaderFilename,
                     const std::string & geometryShaderFilename               = "",
                     const std::string & tessellationControlShaderFilename    = "",
                     const std::string & tessellationEvaluationShaderFilename = "");

        virtual ~Shader();

        void setMat3(const std::string & uniformName, const glm::mat3 & matrix);
        void setMat4(const std::string & uniformName, const glm::mat4 & matrix);
        void setVec3(const std::string & uniformName, const glm::vec3 & vector);
        void setInt(const std::string & uniformName, int value);
        void setFloat(const std::string & uniformName, float value);

        void apply();
    };
}

#endif //OPENGLGP_SHADER_H
