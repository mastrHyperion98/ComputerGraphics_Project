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

#include <TerrainGenerator.h>
#include "World.h"
#include "TreeGenerator.h"
#include "random"
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
    TerrainGenerator terrainGenerator;
    TerrainV2 *terrain = terrainGenerator.GenerateTerrain(512, 512, 4, 0.25, 20, 4);
    world_entities.push_back(terrain);
    for(int i = -30; i < 31; i++){
        for(int j = 0; j > -61; j--){
            if ((RandNumGen(0, RAND_MAX) > 0.9975 * RAND_MAX)) {
                vec3 position = vec3 (i, 0, j);
                AddEntities(TreeGenerator::generateTree(vec3{i, TerrainV2::getHeightAtPosition(position), j}));
            }
        }
    }
    std::cout << 'h' << std::endl;
}

int World::RandNumGen(int min, int max) {
    if(min < 0){
        min = 0;
    }
    if(max < min){
        max = min;
    }
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(min,max); // dist
    return dist(rng);
}
