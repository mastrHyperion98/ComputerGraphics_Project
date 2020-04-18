//
// Created by hyperion on 2020-04-16.
//

#ifndef INC_371PROCEDURALFOREST_TERRAINV2_H
#define INC_371PROCEDURALFOREST_TERRAINV2_H

#include "Entity.h"
#include <map>
#include "glm/glm.hpp"
#include <vector>
typedef std::pair<std::vector<float>, int> terrain_key;
// map a terrain position to a height value
typedef std::map<std::vector<float>, int> height_map;


class TerrainV2: public Entity{
public:
    TerrainV2();
    virtual void Draw();
   // virtual void Update();
    void addPositionOffset(glm::vec3);
    static int getHeightAtPosition(glm::vec3);
    static void addPositionToMap(glm::vec3);
    void createVAO();

private:
    Material terrain_mat;
    Material terrain_mat_top;
    // stores the height at every position
    static height_map terrain_map;
    // list of position offset from (0,0,0)
    std::vector<glm::vec3> positionOffset;
    // will be used once we do instanced drawing
    GLuint vao;

    unsigned int instanceVBO;

};

struct TexturedVertex
{
    TexturedVertex(vec3 _position, vec3 _normal, vec2 _uv, float _texture_id)
            : position(_position), normal(_normal),uv(_uv), texture_id{_texture_id} {}

    vec3 position;
    vec3 normal;
    vec2 uv;
    float texture_id;
};


#endif //INC_371PROCEDURALFOREST_TERRAINV2_H
