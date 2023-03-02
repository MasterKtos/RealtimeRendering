//
// Created by MasterKtos on 26.11.2022.
//

#include "HousingEstate/SceneNode.h"

#include <utility>
#include "glm/ext/matrix_transform.hpp"

SceneNode::SceneNode(std::string nodeName) : name(std::move(nodeName)) {
    transform.position = glm::vec3(0);
    transform.rotation = glm::vec3(0);
    transform.scale = glm::vec3(1);
    transformMat = glm::mat4(1.0f);
}

void SceneNode::AddParent(std::shared_ptr<SceneNode> newParent) {
    parent = std::move(newParent);
}

void SceneNode::AddChild(std::shared_ptr<SceneNode> child) {
    children.push_back(child);
    children.back()->AddParent(shared_from_this());
}

std::shared_ptr<SceneNode> SceneNode::GetNode(std::string searchedName) {
    if(name == searchedName)
        return shared_from_this();
    if(children.empty()) return nullptr;

    for(auto child : children) {
         auto childResult = child->GetNode(searchedName);
         if(childResult != nullptr)
             return childResult->shared_from_this();
    }
    return nullptr;
}

void SceneNode::UpdateTransform() {
    glm::mat4 rotationMat = glm::rotate(glm::mat4(1.0f),
                                        glm::radians(transform.rotation.x),
                                        glm::vec3(1, 0, 0));
    rotationMat = glm::rotate(rotationMat,
                              glm::radians(transform.rotation.y),
                              glm::vec3(0, 1, 0));
    rotationMat = glm::rotate(rotationMat,
                              glm::radians(transform.rotation.z),
                              glm::vec3(0, 0, 1));

    glm::mat4 positionMat = glm::translate(glm::mat4(1.0f), transform.position);

    glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), transform.scale);

    glm::mat4 parentMat(1.0f);
    if(parent) parentMat = parent->GetTransform();

    transformMat = parentMat * positionMat * rotationMat * scaleMat;

    for(auto child : children) {
        child->UpdateTransform();
    }
}

glm::mat4 SceneNode::GetTransform() const {
    return transformMat;
}

void SceneNode::Move(glm::vec3 newPosition) {
    transform.position = newPosition;
    UpdateTransform();
}

void SceneNode::Rotate(glm::vec3 newRotation) {
    transform.rotation = newRotation;
    UpdateTransform();
}

void SceneNode::Scale(glm::vec3 newScale) {
    transform.scale = newScale;
    UpdateTransform();
}
