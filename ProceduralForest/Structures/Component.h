//
// Created by Steven Smith on 2020-03-07.
//

#ifndef ASSIGNMENT2_COMPONENT_H
#define ASSIGNMENT2_COMPONENT_H

#include <GL/glew.h>
#include "glm/glm.hpp"  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include "glm/gtc/matrix_transform.hpp" // include this to create transformation matrices
#include "glm/common.hpp"
#include "glm/gtc/quaternion.hpp"
#include "Transform.h"
#include "../framework/shader.h"
#include "Material.h"
class Component {
public:
    Component(Shader, Material);
    virtual GLuint createVertexArrayObject();
    virtual void Draw(Transform, Transform, int);
    void Translate(glm::vec3 translate);
    void Rotate(float angle, vec3 trans);
    void Scale(glm::vec3 scale);
    Transform transform;
protected:
    Material material;
    Shader shaderProgram;
    GLuint vao;
    int number_of_parts;
    glm::mat4 modelWorldMatrix = mat4(1.0f);
};


#endif //ASSIGNMENT2_COMPONENT_H
