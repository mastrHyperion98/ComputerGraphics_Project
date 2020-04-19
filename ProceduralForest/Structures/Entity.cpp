//
// Created by Steven Smith on 2020-03-07.
// Created for Concordia W 2020 Comp 371
//
/* Entity class can be use as is but can be extended if more specialized models are needed.
 * An example of this is the Tree class which is highly specialized to print Trees. This and
 * the Component class relies heavily on the inheritance and polymorphism principles of OOP.
 */

#include "Entity.h"
#include <vector>
#include "GL/glew.h"    // Include GLEW - OpenGL Extension Wrangler
#include "glm/gtc/quaternion.hpp"


Entity::Entity():components{std::vector<Component*>()}, transform{new Transform}{

}
Entity::~Entity(){
    for(auto entries:components){
        delete entries;
        entries=nullptr;
    }
    delete transform;
}

void Entity::SetPosition(vec3 pos){
    transform->position = pos;

}

void Entity::Translate(glm::vec3 translate){
    transform->position += translate;
}
void Entity::Rotate(float angle, glm::vec3 rotate){
    quat rotated_point = angleAxis(angle, rotate);
    transform->rotation *= rotated_point;
}
void Entity::Scale(glm::vec3 scale){
    transform->scaling += scale;
}
void Entity::Translate(int component, glm::vec3 translate){
    components[component]->Translate(translate);
}
void Entity::Rotate(int component, float angle, glm::vec3 rotate){
    components[component]->Rotate(angle, rotate);
}
void Entity::Scale(int component, glm::vec3 scale){
    components[component]->Scale(scale);
}
void Entity::ResetPosition(){
    transform->position = vec3(0,0,0);
}
void Entity::ResetRotation(){
    transform->rotation =  angleAxis(radians(0.0f), vec3(0.0f,0.0f,0.0f));
}
void Entity::ResetScaling(){
    transform->scaling = vec3(1,1,1);
}
void Entity::Draw(){
    transform->transformation = mat4(1.0f);
    transform->transformation = translate(transform->transformation, transform->position);
    transform->transformation = transform->transformation * mat4_cast(transform->rotation);
    transform->transformation = scale(transform->transformation, transform->scaling);
    for(auto & component : components)
        component->Draw();
}
void Entity::addComponent(Component* component){
    components.push_back(component);
    component->setParent(transform);
}

Entity::Entity(const Entity &entity) {
    transform = new Transform(*entity.transform);
    components = std::vector<Component*>(entity.components);
}

Entity& Entity::operator=(const Entity &entity) {
    if(&entity == this)
        return *this;

    transform = new Transform(*entity.transform);
    components = std::vector<Component*>(entity.components);

    return *this;
}

void Entity::Update() {

}
Transform* Entity::getTransform() {
    return transform;
}

void Entity::removeComponent(int position) {
    components.erase(components.begin() + position);
}

int Entity::getSize() {
    return components.size();
}

