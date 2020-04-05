//
// Created by hyperion on 2020-03-08.
//
#ifndef ASSIGNMENT2_CUBE_H
#define ASSIGNMENT2_CUBE_H

#include "Component.h"

class Cube: public Component {
public:
    Cube(Entity&, Material);
    virtual void Draw() override ;
    virtual GLuint createVertexArrayObject() override;
};


#endif //ASSIGNMENT2_CUBE_H
