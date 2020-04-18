//
// Created by hyperion on 2020-04-16.
//
// An approximation of the Perlin Noise Algorithm. The code is based off Javidx youtube video
// Programming Perlin-like Noise (C++) https://www.youtube.com/watch?v=6-0UaeJBumA
// This will hopefully be used to generate terrain our terrain and hopefully add a 3rd coordinate
//

#include <algorithm>
#include "TerrainGenerator.h"
#include <iostream>
#include <random>
#include "Cube.h"

TerrainV2* TerrainGenerator::GenerateTerrain(int width, int height, int octaves, float bias, float height_multiplier,int n_terrains) {
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution(0.0,1.0);
    TerrainV2 *terrain = new TerrainV2();
    // set our field parameters for the noise
    int n_width = width;
    int n_height = height;
    int n_octaves = octaves;
    float sBias = bias;
    int n_blocks = width*height;
    int n_block_per_terrain= n_blocks/n_terrains;
    // create our noise
    float * noise_seed = new float[n_width * n_height];
    float * noise;
    // Now we generate our noise seed this is what we will interpolate to create our mapping.
    // fill it up with random numbers between 0 and 1
    for (int i = 0; i < n_width * n_height; i++) noise_seed[i] = distribution(generator);
    // then we generate out noise
    noise = GenerateNoise(n_width, n_height, noise_seed, n_octaves, sBias);
    int blocks = 0;
    for (int x = 0; x < n_width; x++) {
        for (int y = 0; y < n_height; y++) {
            if(blocks == n_block_per_terrain){
                delete noise;
                for (int i = 0; i < n_width * n_height; i++) noise_seed[i] = distribution(generator);
                noise =  GenerateNoise(n_width, n_height, noise_seed, n_octaves, sBias);
            }
            // grab our height from our array of noise
            int height = (int) ( noise[y * n_width + x] * height_multiplier);
            // fill the void between -1 and height
            for(int k = 0; k < height; k++){
                glm::vec3 position(x, k, -y);
                // add position
                terrain->addPositionOffset(position);
            }
            glm::vec3 position(x, height, -y);
            terrain->addPositionOffset(position);
            terrain->addPositionToMap(position);
            blocks++;
        }
    }
    terrain->createVAO();
    return terrain;
}
// here we want to output to out fNoise2D, but perhaps we dont want to output directly to our local variable


float * TerrainGenerator::GenerateNoise(int width, int height, float * noise_seed, int n_octaves, float sBias){
    float* output2D =new float[width*height];
    for(int x = 0; x < width;x++){
        for(int y = 0; y < height; y++){
            float f_noise = 0.0f;
            float scale_acc = 0.0f;
            float scale = 1.0f;
            // now we iterate over our number of octaves
            for(int k = 0; k < n_octaves;k++){
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
                float sample_t = (1.0 - blend_x)*noise_seed[sample_y1*width + sample_x1] * noise_seed[sample_y1*width + sample_x2];
                float sample_b = (1.0 - blend_x)*noise_seed[sample_y2*width + sample_x1] * noise_seed[sample_y2*width + sample_x2];
                scale_acc += scale;
                f_noise += (blend_y * (sample_b-sample_t) + sample_t) * scale;
                scale = scale/sBias;
            }
            output2D[y * width + x] = f_noise / scale_acc;
        }
    }

    return output2D;
}