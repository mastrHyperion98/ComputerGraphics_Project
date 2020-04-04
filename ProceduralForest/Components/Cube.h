//
// Created by hyperion on 2020-03-08.
//
#ifndef ASSIGNMENT2_CUBE_H
#define ASSIGNMENT2_CUBE_H

#include "../structures/Component.h"

class Cube: public Component {
public:
    Cube(Shader, Material);
    virtual void Draw(Transform, Transform, int) override ;
    virtual GLuint createVertexArrayObject() override;
};


#endif //ASSIGNMENT2_CUBE_H
