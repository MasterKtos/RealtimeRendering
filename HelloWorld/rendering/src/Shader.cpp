//
// Created by MasterKtos on 09.11.2022.
//

#include "include/render/Shader.h"

#include <fstream>
#include <glm/gtc/type_ptr.hpp>

RenderBase::Shader::Shader(const std::string &vertexShaderFilename, const std::string &fragmentShaderFilename,
                           const std::string &geometryShaderFilename,
                           const std::string &tessellationControlShaderFilename,
                           const std::string &tessellationEvaluationShaderFilename) {
    const std::string shaderCodes[5] = { loadFile(vertexShaderFilename),
                                         loadFile(fragmentShaderFilename),
                                         loadFile(geometryShaderFilename),
                                         loadFile(tessellationControlShaderFilename),
                                         loadFile(tessellationEvaluationShaderFilename) };

    const std::string filenames[5] = { vertexShaderFilename,
                                       fragmentShaderFilename,
                                       geometryShaderFilename,
                                       tessellationControlShaderFilename,
                                       tessellationEvaluationShaderFilename };

    programID = glCreateProgram();

    if (programID == 0)
    {
        fprintf(stderr, "Error while creating program object.\n");
        printf("Press any key to continue...\n");
        getchar();
        return;
    }

    for (int i = 0; i < sizeof(shaderCodes) / sizeof(std::string); ++i)
    {
        if (shaderCodes[i].empty())
            continue;

        GLuint shaderType = 0;

        switch(i) {
            case 0: shaderType = GL_VERTEX_SHADER; break;
            case 1: shaderType = GL_FRAGMENT_SHADER; break;
            case 2: shaderType = GL_GEOMETRY_SHADER; break;
            case 3: shaderType = GL_TESS_CONTROL_SHADER; break;
            case 4: shaderType = GL_TESS_EVALUATION_SHADER; break;
            default: break;
        }

        if (shaderType == 0)
        {
            fprintf(stderr, "Error! Wrong shader type.\n");
            continue;
        }

        GLuint shaderObject = glCreateShader(shaderType);

        if (shaderObject == 0)
        {
            fprintf(stderr, "Error while creating %s.\n", filenames[i].c_str());
            continue;
        }

        const char *shaderCode[1] = { shaderCodes[i].c_str() };

        glShaderSource (shaderObject, 1, shaderCode, nullptr);
        glCompileShader(shaderObject);

        GLint result;
        glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &result);

        if (result == GL_FALSE)
        {
            fprintf(stderr, "%s compilation failed!\n", filenames[i].c_str());

            GLint logLen;
            glGetShaderiv(shaderObject, GL_INFO_LOG_LENGTH, &logLen);

            if (logLen > 0)
            {
                char * log = (char *)malloc(logLen);

                GLsizei written;
                glGetShaderInfoLog(shaderObject, logLen, &written, log);

                fprintf(stderr, "Shader log: \n%s", log);
                free(log);
            }

            continue;
        }

        glAttachShader(programID, shaderObject);
        glDeleteShader(shaderObject);
    }

    link();
}

bool RenderBase::Shader::link() {
    glLinkProgram(programID);

    GLint status;
    glGetProgramiv(programID, GL_LINK_STATUS, &status);

    if (status == GL_FALSE)
    {
        fprintf(stderr, "Failed to link shader program!\n");

        GLint logLen;
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logLen);

        if (logLen > 0)
        {
            char* log = (char*)malloc(logLen);
            GLsizei written;
            glGetProgramInfoLog(programID, logLen, &written, log);

            fprintf(stderr, "Program log: \n%s", log);
            free(log);
        }
    }
    else
        isLinked = true;

    return isLinked;
}

RenderBase::Shader::~Shader() {
    glDeleteProgram(programID);
}

void RenderBase::Shader::apply() {
    if (isLinked)
        glUseProgram(programID);
}

std::string RenderBase::Shader::loadFile(const std::string &filename) {
    if (filename.empty())
        return "";

    std::string filetext;
    std::string line;

    std::ifstream inFile("res/shaders/" + filename);

    if (!inFile)
    {
        fprintf(stderr, "Could not open file %s", filename.c_str());
        inFile.close();

        return "";
    }
    else
    {
        while (getline(inFile, line))
            filetext.append(line + "\n");
        inFile.close();

        return filetext;
    }
}

void RenderBase::Shader::setMat3(const std::string &uniformName, const glm::mat3 &matrix) {
    glUniformMatrix3fv(glGetUniformLocation(programID, uniformName.c_str()), 1, GL_FALSE, &matrix[0][0]);
}

void RenderBase::Shader::setMat4(const std::string &uniformName, const glm::mat4 &matrix) {
    glUniformMatrix4fv(glGetUniformLocation(programID, uniformName.c_str()), 1, GL_FALSE, &matrix[0][0]);
}

void RenderBase::Shader::setVec3(const std::string &uniformName, const glm::vec3 &vector) {
    glProgramUniform3fv(programID, glGetUniformLocation(programID, uniformName.c_str()), 1, glm::value_ptr(vector));
}

void RenderBase::Shader::setInt(const std::string &uniformName, int value) {
    glUniform1i(glGetUniformLocation(programID, uniformName.c_str()), value);
}

void RenderBase::Shader::setFloat(const std::string &uniformName, float value) {
    glUniform1f(glGetUniformLocation(programID, uniformName.c_str()), value);
}
