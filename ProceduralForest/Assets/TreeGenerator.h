//
// Created by hyperion on 2020-04-05.
//
// Modified by RemineralizedWater(Michael Rowe) on 2020-04-08
// Student ID: 26101267
//

#ifndef INC_371PROCEDURALFOREST_TREEGENERATOR_H
#define INC_371PROCEDURALFOREST_TREEGENERATOR_H

#include <Entities/Tree.h>
#include "Entity.h"

class TreeGenerator {
public:
    static Tree* generateTree(vec3);
private:
    static void generateTrunk(Tree&, int);
    static void generateLeaves(Tree&, int, vec3);
    static float euclidianNorm(vec3, vec3);
    static bool inSphere(vec3, vec3, float);
    static int computeNumberInX(vec3 center, float radius, int index, int increment);
    static int computeNumberInZ(vec3 position, vec3 center, float radius, int index, int increment);
    static int const MIN_ANGLE = 0;
    static int const MAX_ANGLE = 90;
    static vec3 const ROTATION_AXIS;
};


#endif //INC_371PROCEDURALFOREST_TREEGENERATOR_H
