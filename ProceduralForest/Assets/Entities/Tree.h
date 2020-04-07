//
// Created by hyperion on 2020-04-05.
//

#ifndef INC_371PROCEDURALFOREST_TREE_H
#define INC_371PROCEDURALFOREST_TREE_H

#include "Entity.h"
#include <vector>
#include "glm/glm.hpp"
#include "Cube.h"

struct TreeOffsetData{
    vec3 offset;
    float textureOffset;
};
class Tree: public Entity{
public:
    void virtual Draw() override ;
    void virtual Update() override;
    void addLeavesOffset(TreeOffsetData);
    std::vector<TreeOffsetData> getLeavesOffsets(){return data_offset;};
    void removeLeavesOffset(int);
    void setTrunkHeight(int);
    void createVAO();
    std::vector<TreeOffsetData> data_offset;
private:
    Material leaves;
    Material trunk;
    int trunk_height{0};
    GLuint vao;
    unsigned int instanceVBO;
};


#endif //INC_371PROCEDURALFOREST_TREE_H
