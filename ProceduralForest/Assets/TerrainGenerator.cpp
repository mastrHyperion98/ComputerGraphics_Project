//
// Created by hyperion on 2020-04-16.
//
// A noise approximation of the Perlin Noise Algorithm. The code is based off Javidx youtube video
// Programming Perlin-like Noise (C++) https://www.youtube.com/watch?v=6-0UaeJBumA
// This will hopefully be used to generate terrain our terrain and hopefully add a 3rd coordinate
//

#include <algorithm>
#include "TerrainGenerator.h"
#include <iostream>
#include <random>
#include "Cube.h"
TerrainGenerator::TerrainGenerator() {

}

TerrainGenerator::~TerrainGenerator() {
    delete fNoise2D;
    delete fNoiseSeed2D;
}

TerrainV2* TerrainGenerator::GenerateTerrain(int width, int height, int octaves, float bias) {
    TerrainV2 *terrain = new TerrainV2();
    // set our field parameters for the noise
    int nOutputWidth = width;
    int nOutputHeight = height;
    int nOctaves = octaves;
    float sBias = bias;
    // create our noise
    fNoiseSeed2D = new float[nOutputWidth * nOutputHeight];
    fNoise2D = new float[nOutputWidth * nOutputHeight];
    // Now we generate our noise seed this is what we will interpolate to create our mapping.
    // fill it up with random numbers between 0 and 1
    for (int i = 0; i < nOutputWidth * nOutputHeight; i++) fNoiseSeed2D[i] = (float) random() / (float)  RAND_MAX;
    // then we generate out noise
    GenerateNoise(nOutputWidth, nOutputHeight, nOctaves, sBias, fNoise2D);
    for (int x = 0; x < nOutputWidth; x++) {
        for (int y = 0; y < nOutputHeight; y++) {
            int height = (int) ( fNoise2D[y * nOutputWidth + x] * 12.0f);
            // fill the void between -1 and height
            for(int k = -1; k < height; k++){
                glm::vec3 position(x, k, -y);
                // add position
                terrain->addPositionOffset(position);
            }
            glm::vec3 position(x, height, -y);
            terrain->addPositionOffset(position);
            terrain->addPositionToMap(position);
        }
    }
    terrain->createVAO();
    return terrain;
}
// here we want to output to out fNoise2D, but perhaps we dont want to output directly to our local variable
void TerrainGenerator::GenerateNoise(int width, int height, int nOctaveCount, float sBias, float* output2D){
    for(int x = 0; x < width;x++){
        for(int y = 0; y < height; y++){
            float f_noise = 0.0f;
            float scale_acc = 0.0f;
            float scale = 1.0f;
            // now we iterate over our number of octaves
            for(int k = 0; k < nOctaveCount;k++){
                int pitch = width >> k;
                // perform integer division to lose some accuracy resulting in improved realism
                int sample_x1 = (x/pitch)*pitch;
                int sample_y1 = (y/pitch)*pitch;
                // since we are in 2D we need to use a second sample
                int sample_x2 = (sample_x1+pitch)%width;
                int sample_y2=  (sample_y1+pitch)%width;

                float blend_x = (float)(x-sample_x1)/(float)(pitch);
                float blend_y = (float)(y-sample_y1)/(float)(pitch);
                // linear interpolation
                float sample_t = (1.0 - blend_x)*fNoiseSeed2D[sample_y1*width + sample_x1] * fNoiseSeed2D[sample_y1*width + sample_x2];
                float sample_b = (1.0 - blend_x)*fNoiseSeed2D[sample_y2*width + sample_x1] * fNoiseSeed2D[sample_y2*width + sample_x2];
                scale_acc += scale;
                f_noise += (blend_y * (sample_b-sample_t) + sample_t) * scale;
                scale = scale/sBias;
            }
            output2D[y * width + x] = f_noise / scale_acc;
        }
    }
}