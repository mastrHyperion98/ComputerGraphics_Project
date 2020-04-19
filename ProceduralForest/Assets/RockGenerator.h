//
// Created by Kali on 2020-04-18.
//

#ifndef INC_371PROCEDURALFOREST_ROCKGENERATOR_H
#define INC_371PROCEDURALFOREST_ROCKGENERATOR_H

#include <Entities/Rock.h>
#include "Entity.h"

class RockGenerator {
public:
    static Rock* generateRock(vec3);
private:
    static void generateShape(Rock&, int, vec3);
    static float euclidianNorm(vec3, vec3);
    static bool inSphere(vec3, vec3, float);
    static int computeNumberInX(vec3 center, float radius, int index, int increment);
    static int computeNumberInZ(vec3 position, vec3 center, float radius, int index, int increment);
    static int const MIN_ANGLE = 0;
    static int const MAX_ANGLE = 90;
    static vec3 const ROTATION_AXIS;
};


#endif //INC_371PROCEDURALFOREST_ROCKGENERATOR_H
