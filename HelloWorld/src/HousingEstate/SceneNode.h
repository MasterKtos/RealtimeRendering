//
// Created by MasterKtos on 26.11.2022.
//

#ifndef OPENGLGP_SCENENODE_H
#define OPENGLGP_SCENENODE_H


#include <memory>
#include <vector>
#include <string>
#include "glm/vec3.hpp"
#include "glm/ext/matrix_float4x4.hpp"

struct Transform {
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
};

class SceneNode : public std::enable_shared_from_this<SceneNode> {
private:
    std::string name;

protected:
    std::shared_ptr<SceneNode> parent;
    std::vector<std::shared_ptr<SceneNode>> children;
    Transform transform;
    glm::mat4 transformMat;

public:
    SceneNode(std::string nodeName);

    void AddParent(std::shared_ptr<SceneNode> newParent);
    void AddChild(std::shared_ptr<SceneNode> child);

    /// Search for node recursively by name
    /// \param searchedName - Searched node name
    /// \return Found SceneNode or nullptr if nothing was found
    std::shared_ptr<SceneNode> GetNode(std::string searchedName);

    virtual void UpdateTransform();
    virtual glm::mat4 GetTransform() const;

    virtual void Move(glm::vec3 newPosition);
    virtual void Rotate(glm::vec3 newRotation);
    virtual void Scale(glm::vec3 newScale);
};


#endif //OPENGLGP_SCENENODE_H
