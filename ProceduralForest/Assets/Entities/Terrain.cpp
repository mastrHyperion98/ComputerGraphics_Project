//
// Created by hyperion on 2020-04-07.
//
// Modified by RemineralizedWater(Michael Rowe) on 2020-04-08
// Student ID: 26101267
//
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
    std::string texture_list[3]{"../Assets/Textures/grass3.bmp",
                "../Assets/Textures/grass2.png", "../Assets/Textures/forest_path.jpg"};
    int path_index{2};
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(MIN, MAX); // dist
    std::uniform_int_distribution<std::mt19937::result_type> text_random(0, 1); // dist

    depth = dist(rng);
    while(depth % TILE_SCALE != 0 || depth % 2 != 0){
        depth = dist(rng);
    }

  do{
        width = dist(rng);
    } while(width % TILE_SCALE != 0 || width % 2 != 0);
    int texture_index=text_random(rng);
    std::uniform_int_distribution<std::mt19937::result_type> width_coord_random(width/2, width ); // dist
    std::uniform_int_distribution<std::mt19937::result_type> depth_coord_random(depth/2, depth ); // dist
    vec3 path_start{0,0,0};
    vec3 path_end = generateEndPoint();

    Material path;
    path.addTexture(texture_list[path_index].c_str());
    Material ground;
    ground.addTexture(texture_list[texture_index].c_str());
    vec3 scale{TILE_SCALE, 0.1, TILE_SCALE};
    std::vector<vec3> pathPositions = GeneratePathMapping(path_start, path_end);

    int component_index = 0;
    for(int i = 0; (TILE_SCALE*i) <= width; i++){
        vec3 position;
        for(int j = 0; TILE_SCALE*j <= depth; j++){
            position = vec3((TILE_SCALE*i) - width/2, 0, -TILE_SCALE*j);
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

    int segment_size = 4;
    // since width and depth are divisable by the tile width than there exist a solution using x fragments to read it.
    int z_distance =abs(end.z - position.z);
    int z_segment = z_distance / TILE_SCALE;

    int x_distance = (end.x - start.x);
    int x_segment =abs(x_distance)/TILE_SCALE;

    if(x_distance < 0) {
        for(int i = 0; i < segment_size; i++) {
            position = vec3(TILE_SCALE, 0, 0) + position;
            positionMapping.push_back(position);
            x_distance = x_distance  - (TILE_SCALE);
            x_segment++;
        }

    }
    else{
        for(int i = 0; i < segment_size; i++) {
            position = vec3(-1 * TILE_SCALE, 0, 0) + position;
            positionMapping.push_back(position);
            x_segment++;
            x_distance = x_distance +  TILE_SCALE;
        }
    }
    bool down{true};
    while(position != end) {
        std::cout << "END: "  << end.x << '\t' << end.y << '\t' << end.z << std::endl;
        // check which direction
    if(down){
        for(int i = 0; i < segment_size && (z_segment > 0 && position.z > -depth);i++){
            position = vec3(0, 0, -TILE_SCALE) + position;
            positionMapping.push_back(position);
            z_segment--;
            z_distance = z_distance - TILE_SCALE;
        }
        down = false;
    }else{
        down = true;
        if(x_distance < 0){
            for(int i = 0; i < segment_size && x_segment != 0; i++) {
                position = vec3(-1 * TILE_SCALE, 0, 0) + position;
                positionMapping.push_back(position);
                x_segment--;
                x_distance = x_distance + TILE_SCALE;
            }

        }else if(x_distance > 0){
            for(int i = 0; i < segment_size && x_segment != 0; i++) {
                position = vec3(TILE_SCALE, 0, 0) + position;
                positionMapping.push_back(position);
                x_segment--;
                x_distance = x_distance - TILE_SCALE;
            }
        }
    }
        std:: cout << position.x << '\t' << position.y << '\t' << position.z << std::endl;
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

bool Terrain::isAdjacentIn(const vec3 position, std::vector<vec3> positionContainer) {
    vec3 down = position + (vec3(0,0,-TILE_SCALE));
    vec3 up = position + (vec3(0,0,TILE_SCALE));
    vec3 left = position + (vec3(-TILE_SCALE,0,0));
    vec3 right = position + (vec3(TILE_SCALE,0,0));

    for(int i = 0; i < positionContainer.size(); i++){
        if(down == positionContainer[i] ||up == positionContainer[i] || left == positionContainer[i] || right == positionContainer[i])
            return true;
    }

    return false;
}

vec3 Terrain::generateEndPoint() {
    int depth_min = depth/2;
    int lw_bound = -width/2;
    int rw_bound = width/2;

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(lw_bound, rw_bound); // dist
    std::uniform_int_distribution<std::mt19937::result_type> dist_depth(depth_min, depth); // dist
    int depth_index;
    int width_index;
    do{
        width_index = dist(rng);
    }while(width_index % TILE_SCALE != 0);

    if(width_index == lw_bound || width_index == rw_bound){
        // compute random depth
        do{
            depth_index = dist_depth(rng);
        }while(depth_index % TILE_SCALE != 0);
    }
    else
        depth_index = depth;

    return vec3(width_index, 0, -depth_index);

}

/*
 * Checks to see if the Terrain Component Index / Position index if
 * terrain is switched to instanced drawing.
 *
 * Returns true if the index is contained within the path_mapping.
 * We do not want to be able set down Entities on the terrain on tiles
 * that are the path.
 */
bool Terrain::isInPath(int index) {
    for(int i = 0; i < path_mapping.size(); i++){
        if(index == path_mapping[i])
            return true;
    }
    return false;
}