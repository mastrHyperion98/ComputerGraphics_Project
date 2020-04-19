//
// Created by Steven Smith on 2020-03-07.
// // Created for Concordia W 2020 Comp 371
// Transform holds transformation information required by COmponents and Entitiy
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "Transform.h"

Transform::Transform() {
    position = vec3(0,0,0);
    scaling = vec3(1,1,1);
    rotation = angleAxis(radians(0.0f), vec3(0.0f,0.0f,0.0f));
    transformation = mat4(1);
    size = vec3(1);
}