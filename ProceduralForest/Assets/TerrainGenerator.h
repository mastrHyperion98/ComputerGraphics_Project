//
// Created by hyperion on 2020-04-16.
//
// A noise approximation of the Perlin Noise Algorithm. The code is based off Javidx youtube video
// Programming Perlin-like Noise (C++) https://www.youtube.com/watch?v=6-0UaeJBumA
// This will hopefully be used to generate terrain our terrain and hopefully add a 3rd coordinate
//
#ifndef INC_371PROCEDURALFOREST_TERRAINGENERATOR_H
#define INC_371PROCEDURALFOREST_TERRAINGENERATOR_H


class TerrainGenerator {
public:
    TerrainGenerator();
    ~TerrainGenerator();
    void GenerateTerrain(int, int, int, float);
private:
    // default 2D value
    float *fNoiseSeed2D = nullptr;
    float *fNoise2D = nullptr;
    void GenerateNoise(int, int, int , float, float*);


};


#endif //INC_371PROCEDURALFOREST_TERRAINGENERATOR_H
