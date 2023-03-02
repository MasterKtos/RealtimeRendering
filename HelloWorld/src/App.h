//
// Created by MasterKtos on 25.11.2022.
//

#ifndef OPENGLGP_APP_H
#define OPENGLGP_APP_H


#include "render/Shader.h"
#include "GLFW/glfw3.h"
#include "include/render/FPPCamera.h"
#include "render/Camera.h"

#include <memory>

class App {
private:
    std::shared_ptr<RenderBase::Shader> texturedShader;
    std::shared_ptr<RenderBase::Shader> lightShader;
    GLFWwindow *window;

    unsigned int VAO, VBO;
    float deltaTime;

    void processInput();
public:
    int ScreenWidth;
    int ScreenHeight;

    Camera camera;

    bool mouseEnabled;

    App();

    void Init();

    void Run();
    void Terminate();
};


#endif //OPENGLGP_APP_H
