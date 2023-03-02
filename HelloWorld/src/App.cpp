//
// Created by MasterKtos on 25.11.2022.
//
#include "App.h"

#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include <iostream>

#include "imgui.h"
#include "imgui_impl/imgui_impl_glfw.h"
#include "imgui_impl/imgui_impl_opengl3.h"
#include "stb_image.h"

#include "HousingEstate/SceneObject.h"
#include "Shapes/House.h"
#include "Shapes/Roof.h"
#include "HousingEstate/SceneNode.h"
#include "HousingEstate/InstancingObject.h"
#include "render/lights/DirectionalLight.h"
#include "render/lights/PointLight.h"
#include "render/lights/SpotLight.h"
#include "Shapes/Ground.h"

App::App() {
    ScreenWidth = 800;
    ScreenHeight = 600;

    deltaTime = 0.0f;

    mouseEnabled = false;
}

void App::Init() {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(ScreenWidth, ScreenHeight,
                              "LearnOpenGL", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    // Configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // Capture cursor
    // --------------
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Build and compile shaders
    // -------------------------
    texturedShader = std::make_shared<RenderBase::Shader>("textured_simple.vert", "textured.frag");
    texturedShader->apply();

    lightShader = std::make_shared<RenderBase::Shader>("basic.vert", "basic.frag");
    lightShader->apply();
}

void App::Run() {
    #pragma region IMGUI SETUP
    // Setup Dear ImGui binding
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460");

    // Setup style
    ImGui::StyleColorsDark();
    ImVec4 clear_color = ImVec4(0.1f, 0.1f, 0.1f, 1.00f);
    ImVec2 settings_window_size = ImVec2(370, 170);
    #pragma endregion

    RenderBase::Mesh cubeMesh(Shape::House::GetWithNormals().vertices,
                              Shape::House::GetWithNormals().indices);
    RenderBase::Mesh pyramidMesh(Shape::Roof::GetWithNormals().vertices,
                                 Shape::Roof::GetWithNormals().indices);
//    RenderBase::Mesh pyramidMesh(Shape::Roof::Get().vertices,
//                                 Shape::Roof::Get().indices);

    auto root = std::make_shared<SceneNode>("root");

    auto house = std::make_shared<SceneObject>(texturedShader, "house");
    house->SetMesh(cubeMesh);
    house->LoadTexture("res/textures/stone.jpg");

    auto roof = std::make_shared<SceneObject>(texturedShader, "roof");
    roof->SetMesh(pyramidMesh);
    roof->LoadTexture("res/textures/stone.jpg");

    auto middle = glm::vec3(0, 0, 0);

    RenderBase::Mesh groundMesh(Shape::Ground::GetWithNormals(1).vertices,
                                Shape::Ground::GetWithNormals().indices);

    // Wireframe mode
    // --------------
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    // Camera setup
    // ------------
    camera.orbitDistance = 10;

    // Lights setup
    // ------------
    RenderBase::Mesh lightMesh(Shape::House::Get(glm::vec3(1.0f)).vertices,
                               Shape::House::Get(glm::vec3(1.0f)).indices);

    auto pointLight = std::make_shared<RenderBase::PointLight>(
            "pointLight", texturedShader, lightShader);
    pointLight->SetMesh(lightMesh);
    pointLight->Scale(glm::vec3(0.5));

    // Set up scene hierarchy
    // ----------------------
    root->AddChild(std::static_pointer_cast<SceneNode>(pointLight));
    root->AddChild(std::static_pointer_cast<SceneNode>(house));
        house->AddChild(std::static_pointer_cast<SceneNode>(roof));

    // Move objects
    // ------------
    house->Move(glm::vec3(0, 0, 0));
    roof->Move(glm::vec3(0, 2, 0));

    std::vector<std::shared_ptr<RenderBase::Light>> lights { pointLight };

    // Add items to display
    // --------------------
    std::vector<std::shared_ptr<IDisplayNode>> displayNodes {
            std::static_pointer_cast<IDisplayNode>(house),
            std::static_pointer_cast<IDisplayNode>(roof)
    };

    float lastFrame = 0.0f;
    float positionToSet[3] = {0, 0, 0};
    float rotationToSet[3] = {0, 0, 0};
    char nameToSet[20] = "root";
    float orbitSpeed = 5;

    // Render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // Calculate delta time
        // --------------------
        float currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput();

        // render
        // ------
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set up shaders
        // --------------
        texturedShader->apply();
        texturedShader->setMat4("projection",
                                camera.Projection((float)ScreenWidth / (float)ScreenHeight));
        texturedShader->setMat4("view", camera.LookAt());

        lightShader->apply();
        lightShader->setMat4("projection",
                             camera.Projection((float)ScreenWidth / (float)ScreenHeight));
        lightShader->setMat4("view", camera.LookAt());

        // Rendering meshes
        // ----------------
        for(const auto& node : displayNodes)
            node->Draw();
        pointLight->Show();

        // Move objects
        // ------------
        float orbitDist = 5;
        pointLight->Move(glm::vec3(
                orbitDist*cos(currentFrame * orbitSpeed),
                5,
                orbitDist*sin(currentFrame * orbitSpeed)));

        #pragma region CREATE SETTINGS WINDOW
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImVec2 settings_window_position = ImVec2(ScreenWidth-settings_window_size.x,
                                                 ScreenHeight-settings_window_size.y);

        // Show a simple window. Begin/End pair creates a named window.
        {
            ImGui::Begin("Controls");
            ImGui::SetWindowSize(settings_window_size);
            ImGui::SetWindowPos(settings_window_position);
            ImGui::ColorEdit3("BG color", (float*)&clear_color);
            ImGui::DragFloat3("Position", positionToSet, 1, 2);
            ImGui::DragFloat3("Rotation", rotationToSet, 1, 0, 360);
            ImGui::DragFloat("Speeen", &orbitSpeed, 1.0f, 0, 50.0f);
            ImGui::InputText("Object", nameToSet, 20);
            if(ImGui::Button("Move")) {
                auto foundNode = root->GetNode(std::string(nameToSet));
                if(foundNode != nullptr) {
                    foundNode->Move(glm::vec3(positionToSet[0],
                                              positionToSet[1],
                                              positionToSet[2]));

                    foundNode->Rotate(glm::vec3(rotationToSet[0],
                                                rotationToSet[1],
                                                rotationToSet[2]));
                }
            }
            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        // Set background color
        glfwMakeContextCurrent(window);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        // Show ImGUI stuff on screen
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        #pragma endregion

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void App::Terminate() {
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
}

void App::processInput() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if(mouseEnabled) return;

    float rotateAngle = 90;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.panAngle += rotateAngle * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.panAngle -= rotateAngle * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.orbitAngle -= rotateAngle * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.orbitAngle += rotateAngle * deltaTime;
}
