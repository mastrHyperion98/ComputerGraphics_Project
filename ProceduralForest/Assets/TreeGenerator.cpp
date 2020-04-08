//
// Created by hyperion(Steven Smith) on 2020-04-05.
// Student ID: 40057065
//
// Modified by RemineralizedWater(Michael Rowe) on 2020-04-08
// Student ID: 26101267
//
/*
* Static tree generator:
 *
 * General Idea: Randomly creates a tree with a randum height between 7 and 20 cube units
 * derive a radius for a sphere from the height of the tree. Fill up the sphere with cubes and
 * randomly remove cubes from the buffer.
 *
 * TO-DO: ADD adjacency check such that cubes that are removed will not cause another cube to be
 * left hanging (TO accomplish using a position mapping )
 * -Randomly rotate the tree
 */
#include "TreeGenerator.h"
#include <cmath>
#include "Cube.h"
#include "Material.h"
#include <iostream>
#include "random"
 Tree* TreeGenerator::generateTree(vec3 position) {
    // generate the tree here and return it.
    Tree *tree = new Tree;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(7,20); // dist
    int trunk_height = dist(rng);
    int radius = max(trunk_height/3, 3);
    generateTrunk( *tree, trunk_height);
    vec3 center{tree->getLeavesOffsets()[tree->getLeavesOffsets().size()-1]};
    generateLeaves(*tree, radius, center);

    tree->setTreeRadius(radius);
    tree->setHeight(trunk_height);
    // set position
    tree->getTransform()->position = position;
    tree->createVAO();
    return tree;
}
void TreeGenerator::generateTrunk( Tree &tree, int num_trunk) {
    vec3 initial_pos{vec3{0,0,0}};
    tree.addLeavesOffset(initial_pos);
    tree.textureOffset.push_back(0);
    for(int i = 1; i < num_trunk; i++) {
        tree.addLeavesOffset(vec3(0, initial_pos.y + (i * 1.0f), 0));
        tree.textureOffset.push_back(0);
    }
}

void TreeGenerator::generateLeaves( Tree &tree, int radius, vec3 center) {
    int square_count{0};
    int buttom_cutoff = 0;//ceilf(radius/2);
    int increment = 1; // unit cube

    std::random_device dev;
    std::mt19937 rng(dev());

    // compute in two halves
    for(int i = 0; i <= radius; i++){
        int num_x = computeNumberInX(center, radius, i, increment);
        for(int j = 0; j <= num_x; j++){
            vec3 position = center + vec3(j, i * increment, 0);
            if(j!=0) {
                tree.addLeavesOffset(position);
                tree.textureOffset.push_back(1);
                square_count++;
            }
            int num_z = computeNumberInZ(position, center, radius,j, increment);
            for(int k = 0;k < num_z; k++){
                position = center + vec3(j, i * increment, k);
                tree.addLeavesOffset(position);
                tree.textureOffset.push_back(1);
                square_count++;

                position = center + vec3(j, i * increment, -k);
                tree.addLeavesOffset(position);
                tree.textureOffset.push_back(1);
                square_count++;

            }
        }
        for(int j = 0; j <= num_x; j++){
            vec3 position = center + vec3(-j, i * increment, 0);
            if(j!=0 ) {
                square_count++;
                tree.addLeavesOffset(position);
                tree.textureOffset.push_back(1);
            }
            int num_z = computeNumberInZ(position, center, radius,j, increment);
            for(int k = 0;k < num_z; k++){
                position = center + vec3(-j, i * increment, k);
                tree.addLeavesOffset(position);
                tree.textureOffset.push_back(1);
                    square_count++;
                position = center + vec3(-j, i * increment, -k);
                tree.addLeavesOffset(position);
                tree.textureOffset.push_back(1);
                square_count++;
            }
        }
    }

    for(int i = 0; i < radius - buttom_cutoff; i++){
        int num_x = computeNumberInX(center, radius, i, increment);
        for(int j = 0; j <= num_x; j++){
            vec3 position = center + vec3(j, -(i * increment), 0);
            if(j!=0) {
                tree.addLeavesOffset(position);
                tree.textureOffset.push_back(1);
                square_count++;
            }
            int num_z = computeNumberInZ(position, center, radius,j, increment);
            for(int k = 0;k < num_z; k++){
                position = center + vec3(j, -(i * increment), k);
                tree.addLeavesOffset(position);
                tree.textureOffset.push_back(1);
                square_count++;

                position = center + vec3(j, -(i * increment), -k);
                tree.addLeavesOffset(position);
                tree.textureOffset.push_back(1);
                square_count++;
            }
        }
        for(int j = 0; j <= num_x; j++){
            vec3 position = center + vec3(-j, -(i * increment), 0);
            if(j!=0) {
                tree.addLeavesOffset(position);
                tree.textureOffset.push_back(1);
                square_count++;
            }
            int num_z = computeNumberInZ(position, center, radius,j, increment);
            for(int k = 0;k < num_z; k++){
                position = center + vec3(-j, -(i * increment), k);

                tree.addLeavesOffset(position);
                tree.textureOffset.push_back(1);
                square_count++;

                position = center + vec3(-j, -(i * increment), -k);
                tree.addLeavesOffset(position);
                tree.textureOffset.push_back(1);
                square_count++;
            }
        }
    }
    // we want to remove x_number of blocks based on the total number of blocks in the tree
    int to_remove = square_count *0.40;

    for(int i = 0; i < to_remove; i++){
        int tree_size = tree.getLeavesOffsets().size() - 1;
        std::uniform_int_distribution<std::mt19937::result_type> dist(square_count/2,tree_size); // distribution in range [1, 6]
        int remove = dist(rng);
        tree.removeLeavesOffset(remove);
        tree.textureOffset.pop_back();
    }


}
float TreeGenerator::euclidianNorm(vec3 point, vec3 center) {
    vec3 vect = point - center;
    float norm = sqrt(pow(vect.x,2)+pow(vect.y,2)+pow(vect.z, 2));
    return norm;
}

bool TreeGenerator::inSphere(vec3 point, vec3 center, float radius) {
    return euclidianNorm(point, center) <= radius;
}
int TreeGenerator::computeNumberInX(vec3 center, float radius, int index, int increment) {
    float y = pow((center.y + index*increment) - center.y, 2);
    float z = 0; // always
    float x = sqrt(pow(radius, 2) - y) + center.x;

    return x;
}

int TreeGenerator::computeNumberInZ(vec3 position, vec3 center, float radius, int index, int increment) {
    float y = pow((center.y + index*increment) - center.y, 2);
    float x = pow(position.x - center.x, 2);

    float z = sqrt(pow(radius, 2) - y - x) + center.z;

    return z;
}