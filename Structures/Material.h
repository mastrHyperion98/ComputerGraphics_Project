//
// Created by hyperion on 2020-04-02.
//
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "stb_image.h"

#ifndef ASSIGNMENT2_MATERIAL_H
#define ASSIGNMENT2_MATERIAL_H
struct Material{
    GLuint diffuseMapId;
    glm::vec3 vertexColor;
    bool isTextured;

    void addTexture(const char *filename) {
        // Step1 Create and bind textures
        GLuint textureId = 0;
        glGenTextures(1, &textureId);
        assert(textureId != 0);


        glBindTexture(GL_TEXTURE_2D, textureId);

        // Step2 Set filter parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // Step3 Load Textures with dimension data
        int width, height, nrChannels;
        unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
        if (!data)
        {
            std::cerr << "Error::Texture could not load texture file:" << filename << std::endl;
            return;
        }

        // Step4 Upload the texture to the PU
        GLenum format = 0;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height,
                     0, format, GL_UNSIGNED_BYTE, data);

        // Step5 Free resources
        stbi_image_free(data);
        //glBindTexture(GL_TEXTURE_2D, 0);
        diffuseMapId = textureId;
        isTextured = true;
    }
};

#endif //ASSIGNMENT2_MATERIAL_H
