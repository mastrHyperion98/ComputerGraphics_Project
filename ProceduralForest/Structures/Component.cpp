//
// Created by Steven Smith on 2020-03-07.
// Created for Concordia W 2020 Comp 371
/*
 * Base Component Class to be used as a component of the Entity class.
 * This class is meant to be extended since Draw and the VAO are not defined and will
 * result in nothing getting printed.
 *
 */
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

 void Component::Draw(){
}
Component::Component(Material material, glm::vec3 size):  material{material},
parent{nullptr}{
    transform.size = size;
}

Component::Component(const Component &component):parent{component.parent}, material{Material(component.material)}{
    transform=component.transform;
}

Component::~Component() {
    // we dont necessarily want to delete the parent if a component is deleted
   parent = nullptr;
}

Component& Component::operator=(const Component& component){
    if(this == & component)
        return *this;

    material = component.material;
    transform = component.transform;
    vao = component.vao;
    *parent = *component.parent;

    return *this;
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

void Component::setMaterial(Material _material)  {
    material = _material;
}

void Component::setParent(Transform *transform) {
    parent = transform;
}


