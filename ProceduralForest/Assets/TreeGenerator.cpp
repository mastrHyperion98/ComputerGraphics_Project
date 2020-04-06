//
// Created by hyperion on 2020-04-05.
//

#include "TreeGenerator.h"
#include <cmath>
#include "Cube.h"
#include "Material.h"
Entity TreeGenerator::generateTree(float scale, float bias, int steps) {
    // generate the tree here and return it.
    if(bias < 0 || bias > 0.99 || steps > 32 || steps < 0 || steps % 2 != 0)
        throw std::exception( );
    int num_block_trunk = ceilf((steps/bias)/scale);
    int num_leaf_levels = ceilf(steps/scale);
    Entity tree;
    generateTrunk(num_block_trunk, vec3(scale), &tree);

    return tree;
}

void TreeGenerator::generateTrunk(int num, vec3 scale , Entity *tree) {
    Material mat;
    mat.addTexture("../Assets/Textures/bark.bmp");
    mat.vertexColor= vec3(0.290196, 0.172549, 0.160784);
    for(int i = 0; i < num; i++) {
        Cube *cube=new Cube{mat, scale};
        tree->addComponent(cube);
        if(i != 0)
            cube->Translate(vec3(0,(tree->getComponent(i-1)->getTransform().size.y*
            tree->getComponent(i-1)->getTransform().scaling.y) +tree->getComponent(i-1)->getTransform().position.y ,0));
    }
}