cmake_minimum_required(VERSION 3.21 FATAL_ERROR)
project(RenderBase DESCRIPTION "Useful classes for rendering")

add_library(${PROJECT_NAME}
        include/render/Mesh.h src/Mesh.cpp
#        src/Model.cpp include/render/Model.h
        src/Shader.cpp include/render/Shader.h
        src/Texture.cpp include/render/Texture.h
        src/Camera.cpp include/render/Camera.h
        include/render/Renderable.h
        src/FPPCamera.cpp include/render/FPPCamera.h
        src/lights/Light.cpp include/render/lights/Light.h
        src/lights/PointLight.cpp include/render/lights/PointLight.h
#        src/lights/SpotLight.cpp include/render/lights/SpotLight.h
#        src/lights/DirectionalLight.cpp include/render/lights/DirectionalLight.h
        )

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
        ${glad_SOURCE_DIR}
        ${stb_image_SOURCE_DIR}
        ${imgui_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} stb_image)
#target_link_libraries(${PROJECT_NAME} assimp)
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} imgui)
target_link_libraries(${PROJECT_NAME} spdlog)
target_link_libraries(${PROJECT_NAME} glm::glm)