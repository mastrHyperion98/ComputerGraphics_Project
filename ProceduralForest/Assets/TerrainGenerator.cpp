//
// Created by hyperion on 2020-04-16.
//
// A noise approximation of the Perlin Noise Algorithm. The code is based off Javidx youtube video
// Programming Perlin-like Noise (C++) https://www.youtube.com/watch?v=6-0UaeJBumA
// This will hopefully be used to generate terrain our terrain and hopefully add a 3rd coordinate
//

#include "TerrainGenerator.h"


TerrainGenerator::TerrainGenerator() {

}

TerrainGenerator::~TerrainGenerator() {
    delete fNoise2D;
    delete fNoiseSeed2D;
}

void TerrainGenerator::GenerateTerrain(int width=256, int height=256, int octaves=1, float bias=2.0f) {
    // set our field parameters for the noise
    int nOutputWidth = width;
    int nOutputHeight = height;
    int nOctaves = octaves;
    float sBias = bias;

    // Now we generate our noise


}

// here we want to output to out fNoise2D, but perhaps we dont want to output directly to our local variable
void GenerateNoise(int width, int height, int nOctaveCount, float sBias, float* output2D=nullptr){

}