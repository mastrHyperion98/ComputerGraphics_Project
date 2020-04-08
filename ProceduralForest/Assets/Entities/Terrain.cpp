//
// Created by hyperion on 2020-04-07.
//
/*
 * Created as an extension of the basic terrain previously used for testing means.
 * The terrain will always be flat. We may consider adding a blocky hill somewhere later, but that is not a priority
 * The terrain will have a randomly placed dirt road that will go from the camera starting point 0,0,0 and end at a random
 * point.
 *
 * The terrain will also choose from a selection of textures to use as its main grass texture for the rest of the forest.
 */

#include "Terrain.h"
#include <random>
#include <cmath>
#include <string>
#include <iostream>
Terrain::Terrain(){
    GenerateTerrain();
}

void Terrain::GenerateTerrain() {
    std::string texture_list[4]{"../Assets/Textures/grass3.bmp", "../Assets/Textures/grass1.jpg",
                "../Assets/Textures/grass2.png", "../Assets/Textures/forest_path.jpg"};
    int path_index{3};
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(MIN, MAX); // dist
    std::uniform_int_distribution<std::mt19937::result_type> text_random(0, 2); // dist

    depth = dist(rng);
    width = dist(rng);
    int texture_index=text_random(rng);
    std::uniform_int_distribution<std::mt19937::result_type> width_coord_random(width/2, width ); // dist
    std::uniform_int_distribution<std::mt19937::result_type> depth_coord_random(depth/2, depth ); // dist
    vec3 path_start{0,0,0};
    int end_x = width_coord_random(rng);
    int end_z =-depth_coord_random(rng);

    while(end_x % TILE_SCALE != 0){
        end_x = width_coord_random(rng);
    }

    while(end_z % TILE_SCALE != 0){
        end_z = -depth_coord_random(rng);
    }
    vec3 path_end{end_x, 0, end_z};

    Material path;
    path.addTexture(texture_list[path_index].c_str());
    Material ground;
    ground.addTexture(texture_list[texture_index].c_str());
    vec3 scale{TILE_SCALE, 0.1, TILE_SCALE};
    std::vector<vec3> pathPositions = GeneratePathMapping(path_start, path_end);

    int component_index = 0;
    for(int i = 0; i < width; i++){
        vec3 position;
        for(int j = 0; j < depth; j++){
            position = vec3(TILE_SCALE*i, 0, -TILE_SCALE*j);
            Cube *tile;
            if(isContainedIn(position, pathPositions)) {
                tile = new Cube(path, scale);
                path_mapping.push_back(component_index);
            }
            else
                tile = new Cube(ground, scale);

            // set position of the tile
            tile->getTransform().position = position;
            // add tile to the components of Terrain
            addComponent(tile);
            // increase component index of the tile;
            component_index++;
        }
    }
}

// generate the Path Mapping to be used to construct
// the random path starting from the origin
// only adjacent does not include diagonals
std::vector<glm::vec3> Terrain::GeneratePathMapping(const vec3 start,const vec3 end) {
    // generate a path from start-point to end-point
    std::vector<glm::vec3> positionMapping;
    vec3 position = start;
    // first three positions are never random....
    positionMapping.push_back(position);
    for(int i= 0; i < 2; i++){
        position = position + vec3(0,0,-TILE_SCALE);
        positionMapping.push_back(position);
    }

    // now we need to get the 3 components from which to go, down, left or right
    while(position != end){
        vec3 down = position + (vec3(0,0,-TILE_SCALE));
        vec3 left = position + (vec3(-TILE_SCALE,0,0));
        vec3 right = position + (vec3(TILE_SCALE,0,0));
        float distance_down = computeDistance(down, end);
        float distance_left = computeDistance(left, end);
        float distance_right = computeDistance(right, end);
        float smallest_distance = min(min(distance_down, distance_left), distance_right);

        if(smallest_distance == distance_down)
            position = down;
        else if(smallest_distance == distance_right)
            position = right;
        else
            position = left;
        // add position to the position map --> continue until we reach the end
        positionMapping.push_back(position);
    }
    return positionMapping;
}
// returns the distance from current position to end point.
// we will be building shortest path from origin to end point.
float Terrain::computeDistance(const vec3 position, const vec3 end) {
    float distance = sqrt(pow(end.x - position.x, 2) + pow(end.y - position.y,2) +
            pow(end.z - position.z, 2));

    return distance;
}


bool Terrain::isContainedIn(const vec3 position, std::vector<vec3> positionContainer) {
    for(std::vector<vec3>::iterator it = positionContainer.begin(); it != positionContainer.end(); it++){
        if(it->x == position.x && it->y == position.y && it->z == position.z)
            return true;
    }

    return false;
}