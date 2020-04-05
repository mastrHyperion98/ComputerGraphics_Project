//
// Created by Steven Smith on 2020-03-07.
//

#include "Entity.h"
#include <vector>
#include "GL/glew.h"    // Include GLEW - OpenGL Extension Wrangler
#include "glm/gtc/quaternion.hpp"


Entity::Entity():components{std::vector<Component*>()}{
}

void Entity::SetPosition(vec3 pos){
    transform.position = pos;

}

void Entity::Translate(glm::vec3 translate){
    transform.position += translate;
}
void Entity::Rotate(float angle, glm::vec3 rotate){
    quat rotated_point = angleAxis(angle, rotate);
    transform.rotation *= rotated_point;
}
void Entity::Scale(glm::vec3 scale){
    transform.scaling += scale;
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
    transform.position = vec3(0,0,0);
}
void Entity::ResetRotation(){
    transform.rotation =  angleAxis(radians(0.0f), vec3(0.0f,0.0f,0.0f));
}
void Entity::ResetScaling(){
    transform.scaling = vec3(1,1,1);
}
void Entity::Draw(){
    transform.transformation = mat4(1.0f);
    transform.transformation = translate(transform.transformation, transform.position);
    transform.transformation = transform.transformation * mat4_cast(transform.rotation);
    transform.transformation = scale(transform.transformation, transform.scaling);
    for(auto & component : components)
        component->Draw();
}
void Entity::addComponent(Component component){
    components.push_back(&component);
}

Entity::Entity(const Entity &entity) {
    transform = Transform(entity.transform);
    components = std::vector<Component*>(entity.components);
}

Entity& Entity::operator=(const Entity &entity) {
    if(&entity == this)
        return *this;

    transform = Transform(entity.transform);
    components = std::vector<Component*>(entity.components);

    return *this;
}

Entity::~Entity() {
    for(int i = 0; i < components.size(); i++) {
        delete components[i];
        // for safe measure
        components[i] = nullptr;
    }
}

