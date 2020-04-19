//
// Created by Steven Smith on 2020-03-07.
//
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#ifndef ASSIGNMENT2_TRANSFORM_H
#define ASSIGNMENT2_TRANSFORM_H

using namespace glm;
struct Transform {
    Transform();
    vec3 position;
    vec3 scaling;
    vec3 size;
    quat rotation;
    mat4 transformation;

};


#endif //ASSIGNMENT2_TRANSFORM_H
