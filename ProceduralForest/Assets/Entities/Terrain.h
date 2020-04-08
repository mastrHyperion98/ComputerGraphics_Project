//
// Created by hyperion on 2020-04-07.
//
// Modified by RemineralizedWater(Michael Rowe) on 2020-04-08
// Student ID: 26101267
//
//

#ifndef INC_371PROCEDURALFOREST_TERRAIN_H
#define INC_371PROCEDURALFOREST_TERRAIN_H
#include "Entity.h"
#include "Tree.h"
#include <vector>
#include <map>

// int is the index to the component in the component list
typedef std::pair<int, std::vector<Tree*>> terrainPair;
typedef std::map<int, std::vector<Tree*>> terrainMap;

class Terrain: public Entity{
public:
    Terrain();
    // function to create the terrain
    void GenerateTerrain();
    int getDepth(){return depth;};
    int getWidth(){return width;};
private:
    const int TILE_SCALE = 1;
    const int MAX= 50;
    const int MIN = 25;
    std::vector<glm::vec3> GeneratePathMapping(const vec3, const vec3);
    float computeDistance(const vec3, const vec3);
    int depth;
    int width;
    terrainMap terrain_mapping;
    std::vector<int> path_mapping;
    bool isContainedIn(const vec3, std::vector<vec3>);
    bool isAdjacentIn(const vec3, std::vector<vec3>);
    vec3 generateEndPoint();
    void GenerateForest();
};


#endif //INC_371PROCEDURALFOREST_TERRAIN_H
