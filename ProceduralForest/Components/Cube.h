//
// Created by hyperion on 2020-03-08.
//
#ifndef ASSIGNMENT2_CUBE_H
#define ASSIGNMENT2_CUBE_H

#include "../Structures/Component.h"

struct TexturedColoredVertex
{
    TexturedColoredVertex(vec3 _position, vec3 _normal, vec2 _uv)
            : position(_position), normal(_normal),uv(_uv) {}

    vec3 position;
    vec3 normal;
    vec2 uv;
};

class Cube: public Component {
public:
    Cube(Material, vec3);
    virtual void Draw() override ;
    virtual GLuint createVertexArrayObject() override;
};


#endif //ASSIGNMENT2_CUBE_H
