//
// Created by RemineralizedWater(Michael Rowe) on 2020-04-18.
// Student ID: 26101267
/*
* Static rock generator:
 *
 * General Idea: Randomly derive a radius for a sphere from the height of the rock. Fill up the sphere with cubes and
 * randomly remove cubes from the buffer.
 */
#include "RockGenerator.h"
#include <cmath>
#include "Cube.h"
#include "Material.h"
#include <iostream>
#include "random"
#include "World.h"

vec3 const RockGenerator::ROTATION_AXIS = vec3(0,1,0);

Rock* RockGenerator::generateRock(vec3 position) {
    // generate the rock here and return it.
    Rock *rock = new Rock;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1,3); // dist
    std::uniform_int_distribution<std::mt19937::result_type> angle_dist(MIN_ANGLE,MAX_ANGLE); // dist
    int radius = dist(rng);
    vec3 center{3,0,0};
    generateShape(*rock, radius, center);

    // set position
    // we can also apply a random rotation to the rock
    rock->getTransform()->position = position;
    rock->Rotate(angle_dist(rng),ROTATION_AXIS);
    rock->createVAO();
    return rock;
}

void RockGenerator::generateShape( Rock &rock, int radius, vec3 center) {
    int square_count{0};
    int increment = 1; // unit cube

    std::random_device dev;
    std::mt19937 rng(dev());

    // compute top half only
    for(int i = 0; i <= radius; i++){
        int num_x = computeNumberInX(center, radius, i, increment);
        for(int j = 0; j <= num_x; j++){
            vec3 position = center + vec3(j, i * increment, 0);
            if(j!=0) {
                rock.addLeavesOffset(position);
                rock.textureOffset.push_back(1);
                square_count++;
            }
            int num_z = computeNumberInZ(position, center, radius, j, increment);
            for(int k = 0;k < num_z; k++){
                position = center + vec3(j, i * increment, k);
                rock.addLeavesOffset(position);
                rock.textureOffset.push_back(1);
                square_count++;

                position = center + vec3(j, i * increment, -k);
                rock.addLeavesOffset(position);
                rock.textureOffset.push_back(1);
                square_count++;

            }
        }
        for(int j = 0; j <= num_x; j++){
            vec3 position = center + vec3(-j, i * increment, 0);
            if(j!=0 ) {
                square_count++;
                rock.addLeavesOffset(position);
                rock.textureOffset.push_back(1);
            }
            int num_z = computeNumberInZ(position, center, radius, j, increment);
            for(int k = 0;k < num_z; k++){
                position = center + vec3(-j, i * increment, k);
                rock.addLeavesOffset(position);
                rock.textureOffset.push_back(1);
                square_count++;
                position = center + vec3(-j, i * increment, -k);
                rock.addLeavesOffset(position);
                rock.textureOffset.push_back(1);
                square_count++;
            }
        }
    }

    // we want to remove x_number of blocks based on the total number of blocks in the rock
    std::uniform_int_distribution<std::mt19937::result_type> dist_to_remove(20,rock.getLeavesOffsets().size() - center.y); // distribution in range [1, 6]
    int to_remove=dist_to_remove(rng); // we want to remove a random number of blocks

    for(int i = 0; i < to_remove; i++){
        // create an list of 10 random points
        int min = center.y;
        int rock_size = rock.getLeavesOffsets().size() - 1;

        if(min >= rock_size)
            break;
        std::vector<int> remove_candidates;
        for(int j = 0; j < dist_to_remove(rng);j++) {
            std::uniform_int_distribution<std::mt19937::result_type> dist(min,rock_size); // distribution in range [1, 6]
            int remove = dist(rng);
            remove_candidates.push_back(remove);
        }

        while(remove_candidates.size() > 1){
            float norm1 = euclidianNorm(rock.getLeavesOffsets()[remove_candidates[0]], center);
            float norm2 = euclidianNorm(rock.getLeavesOffsets()[remove_candidates[1]], center);

            if(norm1 > norm2)
                remove_candidates.erase(remove_candidates.begin()+1);
            else
                remove_candidates.erase(remove_candidates.begin()+0);
        }
        if(rock.getLeavesOffsets().size() > center.y)
            rock.removeLeavesOffset(remove_candidates[0]);
        rock.textureOffset.pop_back();
    }
}

float RockGenerator::euclidianNorm(vec3 point, vec3 center) {
    vec3 vect = point - center;
    float norm = sqrt(pow(vect.x,2)+pow(vect.y,2)+pow(vect.z, 2));
    return norm;
}

bool RockGenerator::inSphere(vec3 point, vec3 center, float radius) {
    return euclidianNorm(point, center) <= radius;
}

int RockGenerator::computeNumberInX(vec3 center, float radius, int index, int increment) {
    float y = pow((center.y + index*increment) - center.y, 2);
    float z = 0; // always
    float x = sqrt(pow(radius, 2) - y) + center.x;

    return x;
}

int RockGenerator::computeNumberInZ(vec3 position, vec3 center, float radius, int index, int increment) {
    float y = pow((center.y + index*increment) - center.y, 2);
    float x = pow(position.x - center.x, 2);

    float z = sqrt(pow(radius, 2) - y - x) + center.z;

    return z;
}