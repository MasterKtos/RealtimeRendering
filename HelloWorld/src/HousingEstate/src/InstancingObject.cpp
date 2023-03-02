//
// Created by MasterKtos on 26.11.2022.
//
#include "glad/glad.h"

#include "HousingEstate/InstancingObject.h"
#include "HousingEstate/InstancedObject.h"
#include "glm/ext/matrix_transform.hpp"

#include <memory>
#include <utility>

InstancingObject::InstancingObject(std::shared_ptr<RenderBase::Shader> shader,
                                   RenderBase::Mesh &instancedMesh, int instancesAmount,
                                   std::string baseInstanceName)
                                   : IDisplayNode(std::move(shader)),
                                     amount(instancesAmount),
                                     baseName(std::move(baseInstanceName)) {
    // Make copy of mesh
    mesh = std::make_shared<RenderBase::Mesh>(instancedMesh);
}

void InstancingObject::Instantiate(std::shared_ptr<SceneNode> parent,
                                   glm::vec3 position) {
    for (int i = 0; i < amount; ++i) {
        instanceTransforms.emplace_back(1.0f);
        instancedMeshes.push_back(std::make_shared<InstancedObject>(
                baseName + std::to_string(i), i,
                shared_from_this()
        ));
        parent->AddChild(instancedMeshes.back());
    }
    
    BindInstanceAttributes();

    // Recalculate transform so that parent transform is included in instance transformMat
    // also move to position if it was specified
    for(const auto& instance : instancedMeshes) {
        if(position != glm::vec3(0))
            instance->Move(position);
        else
            instance->UpdateTransform();
    }
}

void InstancingObject::Instantiate(std::shared_ptr<InstancingObject> parentsInstantiator,
                                   glm::vec3 position) {
    if(parentsInstantiator->instancedMeshes.size() != amount) return;

    for (int i = 0; i < amount; ++i) {
        instanceTransforms.emplace_back(1.0f);
        instancedMeshes.push_back(std::make_shared<InstancedObject>(
                baseName + std::to_string(i), i,
                shared_from_this()
        ));
        parentsInstantiator->instancedMeshes[i]->AddChild(instancedMeshes.back());
    }

    BindInstanceAttributes();

    // Recalculate transform so that parent transform is included in instance transformMat
    // also move to position if it was specified
    for(const auto& instance : instancedMeshes) {
        if(position != glm::vec3(0))
            instance->Move(position);
        else
            instance->UpdateTransform();
    }
}

void InstancingObject::BindInstanceAttributes() {
    glGenBuffers(1, &instanceVBO);
    UpdateInstanceAttributes();

    unsigned int VAO = mesh->VAO;
    glBindVertexArray(VAO);

    // Setup mat4 'model' attribute
    // ----------------------------

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

    // glVertexAttribDivisor(..., 1) - Update buffer per instance loaded
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);

    glBindVertexArray(0);
}

void InstancingObject::UpdateInstanceAttributes() {
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * amount, &instanceTransforms[0], GL_STATIC_DRAW);
}

void InstancingObject::UpdateInstanceTransform(int index, glm::mat4 transformMat) {
    instanceTransforms[index] = transformMat;
    UpdateInstanceAttributes();
}

void InstancingObject::ArrangeInSquare(int squareLength, float distance) {
    for (int i = 0; i < squareLength; ++i) {
        for(int j = 0; j < squareLength; ++j) {
            int index = i*squareLength+j;
            //finish if reached end of InstancedMeshes vector
            if(index > instancedMeshes.size()-1) return;

            instancedMeshes[index]->Move(glm::vec3(i*distance, 0, j*distance));
        }
    }
}

void InstancingObject::Draw() {
    IDisplayNode::Draw();
    shader->apply();
    mesh->DrawInstanced(amount);
}

void InstancingObject::ScaleAll(glm::vec3 newScale) {
    for(const auto& instance : instancedMeshes) {
        instance->Scale(newScale);
    }
}
