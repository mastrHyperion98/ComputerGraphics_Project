//
// Created by Steven Smith on 2020-04-05.
// Created for Concordia W 2020 Comp 371
//
// Modified by RemineralizedWater(Michael Rowe) on 2020-04-08
// Student ID: 26101267
//
 *
 * The world class is an additional layer of abstraction used when drawing our entities
 * The world allows to procedurally generate a world while keeping the main display loop clean.
 *
 * Furthermore, the is composed of a vector list of Entities that allows us to add multiple
 * entities externally or internally and display/update them seemingly.
 */
//

#include <random>
#include "World.h"
#include "TreeGenerator.h"
#include "Terrain.h"
#include <deque>
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

void World::ProcedurallyGenerateWorld() {/*
    // create a basic terrain
    Material simple_ground_material;
    simple_ground_material.addTexture("../Assets/Textures/grass3.bmp");
    // 1500 * 1500 terrain
    Entity *terrain = new Entity;
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

    AddEntities(terrain);
    // several options --> instancing or drawing ~10 cubes and allow for different textures.
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
    }*/
    Terrain *terrain = new Terrain();
    AddEntities(terrain);
    GenerateForest(1, *terrain);
}

/*
 * Generate Trees by randomly positioning them onto the board
 *  density controls the minimum and maximum distance between trees
 *
 *  The denser the forest the more closely packed they are.
 *  A denser forest also has more trees. Therefore we must compute
 *  the number of trees to place. Terrain uses unit cubes so 1 terrrain
 *  component can hold only a single tree.  Not all components will hold trees
 *
 *  A tree cannnot be placed on a position that is a dirt path
 *  A tree cannot be placed if it overlaps over another tree.
 *
 *  uses tree radius to measure its maximum outgoing reach
 *  Radius varies greatly between trees.
 *
 */
void World::GenerateForest(float density, Terrain terrain){
    std::random_device dev;
    std::mt19937 rng(dev());

    // because the terrain is composed of unit cubes
    int row = terrain.getDepth();
    int column= terrain.getWidth();

    // remember that the terrain is generated depth first so column wise
    // this important as it affects the layout of its indices.

    long number_of_tiles = terrain.getNumberOfComponents() -terrain.pathLength();
    // # of tiles represent the absolute maximum number of trees if only trunks were involved
    // Trees have radius ranging from 20/3 to 3
    float average_distance= ((20/3.0) + 3)/2.0 + (1.0/density);
    int number_of_trees = floor(number_of_tiles/average_distance);

    std::uniform_int_distribution<std::mt19937::result_type> dist(0, terrain.getNumberOfComponents()); // dist
    // randomly select a component index that is not on the path
    while(number_of_trees > 0) {
        int index;
        int iterations = 0;
        do {
            index = dist(rng);
            iterations++;
            // continue while tree is on path or on another tree
        } while ((terrain.isInPath(index) && terrain_mapping.find(index) != terrain_mapping.end()) && iterations < 100);
        // if we cannot find a position after 100 iterations exit and leave the forest as is.
        if(iterations == 100)
            break; // safety measure against infinite loops

        // otherwise find the position for our index;
        // Create all Trees at 0,0,0 and then translate to their new positions
        vec3 origin  = vec3(0,0,0);
        vec3 position = terrain.getComponent(index)->getTransform().position;
        // Create a Tree
        Tree *tree;
        float radius;
        iterations = 0;
        do {
            tree = TreeGenerator::generateTree(origin);
            radius = tree->getTreeRadius();
            iterations++;
        }while(!placeTree(radius, index,tree, row, column) && iterations < 100);

            if(iterations == 100)
                break; // cant play true exit
    }
}

using namespace std;
bool World::placeTree(float radius, int index, Tree* tree, int row, int col){
    bool placed{false};
    deque<int> queue;
    queue.push_back(index);
    vector<int> connectingIndices;
    connectingIndices.push_back(index);
    while(radius != 0 && !queue.empty()){
        // do some stuff
        // look up
        index = queue.front();
        if(index % row != 0){
            int new_index = index -1;
            if(terrain_mapping.find(new_index) != terrain_mapping.end())
                return false;
            else if(!indexInQueue(new_index, queue)){
                queue.push_back(new_index);
                connectingIndices.push_back(new_index);
            }
        }
        //look down
        if(index % row != row-1){
            int new_index = index + 1;
            if(terrain_mapping.find(new_index) != terrain_mapping.end())
                return false;
            else if(!indexInQueue(new_index, queue)){
                queue.push_back(new_index);
                if(!indexInVector(new_index, connectingIndices))
                    connectingIndices.push_back(new_index);
            }
        }
        //look left
        if(index % col != col - 1){
            int new_index = index +row;
            if(terrain_mapping.find(new_index) != terrain_mapping.end())
                return false;
            else if(!indexInQueue(new_index, queue)){
                queue.push_back(new_index);
                if(!indexInVector(new_index, connectingIndices))
                    connectingIndices.push_back(new_index);
            }
        }
        // look right
        if(index % col != 0){
            int new_index = index -row;
            if(terrain_mapping.find(new_index) != terrain_mapping.end())
                return false;
            else if(!indexInQueue(new_index, queue)){
                queue.push_back(new_index);

                if(!indexInVector(new_index, connectingIndices))
                    connectingIndices.push_back(new_index);
            }
        }
        // look diagonal left down
        if(index % col != col - 1 && index % row != row-1){
            int new_index = index +(row+1);
            if(terrain_mapping.find(new_index) != terrain_mapping.end())
                return false;
            else if(!indexInQueue(new_index, queue)){
                queue.push_back(new_index);
                if(!indexInVector(new_index, connectingIndices))
                    connectingIndices.push_back(new_index);
            }
        }
        // look diagonal right down
        if(index % col != 0 && index % row != row-1){
            int new_index = index - (row + 1);
            if(terrain_mapping.find(new_index) != terrain_mapping.end())
                return false;
            else if(!indexInQueue(new_index, queue)){
                queue.push_back(new_index);
                if(!indexInVector(new_index, connectingIndices))
                    connectingIndices.push_back(new_index);
            }
        }
        // look diagonal left up
        if(index % row != 0 && index % col != col - 1){
            int new_index = index + (row-1);
            if(terrain_mapping.find(new_index) != terrain_mapping.end())
                return false;
            else if(!indexInQueue(new_index, queue)){
                queue.push_back(new_index);
                if(!indexInVector(new_index, connectingIndices))
                    connectingIndices.push_back(new_index);
            }
        }
        // look diagonal right up
        if(index % col != 0 && index % col != col - 1){
            int new_index = index -(row - 1);
            if(terrain_mapping.find(new_index) != terrain_mapping.end())
                return false;
            else if(!indexInQueue(new_index, queue)){
                queue.push_back(new_index);
                if(!indexInVector(new_index, connectingIndices))
                    connectingIndices.push_back(new_index);
            }
        }
        radius--;
        queue.pop_back();
    }
     return true;
}

bool World::indexInQueue(int index, std::deque<int> queue) {

    for(int & it : queue){
        if(it == index)
            return true;

    }
return false;
}

bool World::indexInVector(int index, std::vector<int> vect) {
    for(int & it : vect){
        if(it == index)
            return true;
    }
    return false;
}