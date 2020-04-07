//
// Created by Steven Smith on 2020-04-05.
//

#include "World.h"

World  World::current;

World::World(){
    current = *this;
}

World::World(const World& world){
    worldTransform = Transform(world.worldTransform);
    world_entities = std::vector<Entity>(world.world_entities);
    current = *this;
}


World::~World() {

}
void World::Draw() {
    for(int i = 0; i < world_entities.size();i++)
        world_entities[i].Draw();

    glBindVertexArray(0);
}

void World::AddEntities(Entity &entity) {
    world_entities.push_back(entity);
}

void World::RemoveEntity(int index){
    if(index >= 0 && index < world_entities.size())
        world_entities.erase(world_entities.begin() + index);
    else
        std::cout << "INDEX OUT OF BOUND! CANNOT REMOVE ENTITY";
}
World& World::getCurrent(){
    return current;
}

void World::Update() {
    for(int i = 0; i < world_entities.size();i++)
        world_entities[i].Update();
}