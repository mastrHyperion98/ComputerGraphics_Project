//
// Created by hyperion on 2020-04-05.
//

#ifndef INC_371PROCEDURALFOREST_TREE_H
#define INC_371PROCEDURALFOREST_TREE_H

#include "Entity.h"
#include <vector>
#include "glm/glm.hpp"
#include "Cube.h"
class Tree: public Entity{
public:
    void virtual Draw() override ;
    void virtual Update() override;
    void addTrunkOffset(glm::vec3);
    void addLeavesOffset(glm::vec3);
    void setCube(Cube* cube);
    std::vector<glm::vec3> getLeavesOffsets(){return offset;};
    void removeLeavesOffset(int);
    void createVAO();
private:
    Material leaves;
    Material trunk;

    std::vector<glm::vec3> offset;
    GLuint vao;
    unsigned int instanceVBO;
};


#endif //INC_371PROCEDURALFOREST_TREE_H
