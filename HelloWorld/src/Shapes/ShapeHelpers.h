//
// Created by MasterKtos on 26.11.2022.
//

#ifndef OPENGLGP_SHAPEHELPERS_H
#define OPENGLGP_SHAPEHELPERS_H

#include <vector>
#include "render/Renderable.h"

namespace Shape {
    struct ShapeObject {
        std::vector<RenderBase::Vertex> vertices;
        std::vector<unsigned int> indices;
    };
}

#endif //OPENGLGP_SHAPEHELPERS_H
