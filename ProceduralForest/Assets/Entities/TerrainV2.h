//
// Created by hyperion on 2020-04-16.
//

#ifndef INC_371PROCEDURALFOREST_TERRAINV2_H
#define INC_371PROCEDURALFOREST_TERRAINV2_H

#include "Entity.h"
#include <map>
#include "glm/glm.hpp"
#include <vector>
#include "Cube.h"
typedef std::pair<std::vector<float>, int> terrain_key;
// map a terrain position to a height value
typedef std::map<std::vector<float>, int> height_map;


class TerrainV2: public Entity{
public:
    TerrainV2();
    virtual void Draw();
   // virtual void Update();
    void addPositionOffset(glm::vec3);
    int getHeightAtPosition(glm::vec3);
    void addPositionToMap(glm::vec3);
    void createVAO();

private:
    Material terrain_mat;
    // stores the height at every position
    height_map terrain_map;
    // list of position offset from (0,0,0)
    std::vector<glm::vec3> positionOffset;
    // will be used once we do instanced drawing
    GLuint vao;

    unsigned int instanceVBO;

};


#endif //INC_371PROCEDURALFOREST_TERRAINV2_H
