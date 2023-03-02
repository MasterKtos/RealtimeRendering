//
// Created by MasterKtos on 27.11.2022.
//

#include "HousingEstate/InstancedObject.h"

InstancedObject::InstancedObject(std::string nodeName, int instanceIndex,
                                 std::shared_ptr<InstancingObject> parentInstancer)
                                 : SceneNode(nodeName), index(instanceIndex),
                                 instancer(std::move(parentInstancer)) {
}

void InstancedObject::UpdateTransform() {
    SceneNode::UpdateTransform();
    instancer->UpdateInstanceTransform(index, transformMat);
}
