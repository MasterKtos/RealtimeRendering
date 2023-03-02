//
// Created by MasterKtos on 26.11.2022.
//

#ifndef OPENGLGP_INSTANCINGOBJECT_H
#define OPENGLGP_INSTANCINGOBJECT_H

#include "render/Mesh.h"
#include "IDisplayNode.h"
#include "SceneNode.h"


/// Takes care of creating and displaying instanced objects
class InstancingObject : public IDisplayNode, public std::enable_shared_from_this<InstancingObject> {
private:
    std::shared_ptr<RenderBase::Mesh> mesh;
    std::string baseName;
    int amount;

    unsigned int instanceVBO;
    std::vector<glm::mat4> instanceTransforms;
    std::vector<std::shared_ptr<SceneNode>> instancedMeshes;

    void BindInstanceAttributes();
    void UpdateInstanceAttributes();
public:
    InstancingObject(std::shared_ptr<RenderBase::Shader> shader,
                     RenderBase::Mesh &instancedMesh, int instancesAmount,
                     std::string baseInstanceName);

    void Instantiate(std::shared_ptr<SceneNode> parent,
                     glm::vec3 position = glm::vec3(0));
    /// This needs number of parents to be equal to the number of instances
    void Instantiate(std::shared_ptr<InstancingObject> parentsInstantiator,
                     glm::vec3 position = glm::vec3(0));

    void UpdateInstanceTransform(int index, glm::mat4 transformMat);

    void ScaleAll(glm::vec3 newScale);

    void ArrangeInSquare(int squareLength, float distance);
    void Draw() override;
};


#endif //OPENGLGP_INSTANCINGOBJECT_H
