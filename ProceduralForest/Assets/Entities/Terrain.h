//
// Created by hyperion on 2020-04-07.
//

#ifndef INC_371PROCEDURALFOREST_TERRAIN_H
#define INC_371PROCEDURALFOREST_TERRAIN_H
#include "Entity.h"
#include "Tree.h"
#include <vector>
#include <map>;

// int is the index to the component in the component list
typedef std::pair<int, std::vector<Tree*>> terrainPair;
typedef std::map<int, std::vector<Tree*>> terrainMap;
class Terrain: public Entity{
public:
    // function to create the terrain
    void GenerateTerrain();
private:
    int depth;
    int width;

};


#endif //INC_371PROCEDURALFOREST_TERRAIN_H
