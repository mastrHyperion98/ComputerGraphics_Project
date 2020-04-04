//
// Created by hyperion on 2020-03-07.
//

#include "Component.h"
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler
#include <GLFW/glfw3.h> // cross-platform interface for creating a graphical context,
// initializing OpenGL and binding inputs
#include "glm/glm.hpp"  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include "glm/gtc/matrix_transform.hpp" // include this to create transformation matrices
#include "glm/common.hpp"
#include "glm/gtc/quaternion.hpp"
#include <iostream>
#include <list>
#include "stb_image.h"

 void Component::Draw(Transform world, Transform entity, int mode){

}

Component::Component(Shader shader, Material material): shaderProgram{shader}, material{material} {
}

void Component::Translate(glm::vec3 translate){
    transform.position += translate;
}
void Component::Rotate(float angle, vec3 trans){
    quat rotated_point = angleAxis(angle, trans);
    transform.rotation *= rotated_point;
}
void Component::Scale(glm::vec3 scale){
    transform.scaling += scale;
}
GLuint Component::createVertexArrayObject() {
    return 1;
}


