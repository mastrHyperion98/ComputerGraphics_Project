//
// Created by Steven Smith on 2020-04-05.
//

#include "World.h"
#include "TreeGenerator.h"
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
    // create a basic terrain
    Material simple_ground_material;
    simple_ground_material.addTexture("../Assets/Textures/grass2.png");
    // 1500 * 1500 terrain
  /*  Entity *terrain = new Entity;
    for(int i = 0; i <10;i++){
        for(int j = 0; j < 10; j++){
            Cube *cube = new Cube(simple_ground_material, vec3(100,0.1,100));
            cube->getTransform().position = (vec3(100*i ,0,-100*j ));
            terrain->addComponent(cube);
        }
    }
    for(int i = 0; i <10;i++){
        for(int j = 0; j < 10; j++){
            Cube *cube = new Cube(simple_ground_material, vec3(100,0.1,100));
            cube->getTransform().position = (vec3(100*i ,0,100*j ));
            terrain->addComponent(cube);
        }
    }

    AddEntities(terrain);*/
    // generate random spacing

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            AddEntities(TreeGenerator::generateTree(vec3{-30 + i*15,0,-j*15}));
        }
    }
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            AddEntities(TreeGenerator::generateTree(vec3{-30 + i*15,0,j*15}));
        }
    }
}