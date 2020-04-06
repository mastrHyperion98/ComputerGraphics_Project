//
// Created by hyperion on 2020-04-05.
//

#ifndef INC_371PROCEDURALFOREST_TREEGENERATOR_H
#define INC_371PROCEDURALFOREST_TREEGENERATOR_H
#include "Entity.h"

class TreeGenerator {
public:
    static Entity generateTree(float scale, float bias, int steps);
private:
    static void generateTrunk(int, vec3, Entity*);
    static void generateLeaves(int steps);
};


#endif //INC_371PROCEDURALFOREST_TREEGENERATOR_H
