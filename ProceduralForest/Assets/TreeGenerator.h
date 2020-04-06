//
// Created by hyperion on 2020-04-05.
//

#ifndef INC_371PROCEDURALFOREST_TREEGENERATOR_H
#define INC_371PROCEDURALFOREST_TREEGENERATOR_H
#include "Entity.h"

class TreeGenerator {
public:
    static Entity generateTree();
private:
    static void generateTrunk(Entity*);
    static void generateLeaves(Entity*);
    static float euclidianNorm(vec3, vec3);
    static bool inSphere(vec3, vec3, float);
    static int computeNumberInX(vec3 center, float radius, int index, int increment);
    static int computeNumberInZ(vec3 position, vec3 center, float radius, int index, int increment);
};


#endif //INC_371PROCEDURALFOREST_TREEGENERATOR_H
