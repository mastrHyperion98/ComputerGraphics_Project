//
// Created by hyperion on 2020-03-07.
//
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "Transform.h"

Transform::Transform() {
    position = vec3(0,0,0);
    scaling = vec3(1,1,1);
    rotation = angleAxis(radians(0.0f), vec3(0.0f,0.0f,0.0f));
    transformation = mat4(1);
}