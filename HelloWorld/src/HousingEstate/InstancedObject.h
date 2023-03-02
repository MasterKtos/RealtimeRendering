//
// Created by MasterKtos on 27.11.2022.
//

#ifndef OPENGLGP_INSTANCEDOBJECT_H
#define OPENGLGP_INSTANCEDOBJECT_H

#include "SceneNode.h"
#include "InstancingObject.h"

/// Represents an instance of an object in SceneGraph
class InstancedObject : public SceneNode {
protected:
    std::shared_ptr<InstancingObject> instancer;
    int index;
public:
    InstancedObject(std::string nodeName, int instanceIndex,
                    std::shared_ptr<InstancingObject> parentInstancer);

    void UpdateTransform() override;
};


#endif //OPENGLGP_INSTANCEDOBJECT_H
