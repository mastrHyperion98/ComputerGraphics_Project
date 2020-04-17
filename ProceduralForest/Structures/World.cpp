//
// Created by Steven Smith on 2020-04-05.
/*// Created for Concordia W 2020 Comp 371
 *
 * THe world class is an additional layer of abstraction used when drawing our entities
 * The world allows to procedurally generate a world while keeping the main display loop clean.
 *
 * Furthermore, the is composed of a vector list of Entities that allows us to add multiple
 * entities externally or internally and display/update them seemingly.
 */
//

#include "World.h"
#include "TreeGenerator.h"
#include "Terrain.h"
World  World::current;

World::World(){
    current = *this;
}

World::World(const World& world){
    worldTransform = Transform(world.worldTransform);
    world_entities = std::vector<Entity*>(world.world_entities);
    current = *this;


}


World::~World() {
for(auto & entries:world_entities){
    delete entries;
    entries = nullptr;
}
}
void World::Draw() {
    for(int i = 0; i < world_entities.size();i++)
        world_entities[i]->Draw();

    glBindVertexArray(0);
}

void World::AddEntities(Entity *entity) {
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
        world_entities[i]->Update();
}

void World::ProcedurallyGenerateWorld() {

}