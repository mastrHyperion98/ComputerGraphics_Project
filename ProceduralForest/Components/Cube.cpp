//
// Created by hyperion on 2020-03-08.
//

#include "Cube.h"
#include "../structures/Component.h"
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler
// initializing OpenGL and binding inputs
#include "glm/glm.hpp"  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language

struct TexturedColoredVertex
{
    TexturedColoredVertex(vec3 _position, vec3 _normal, vec2 _uv)
            : position(_position), normal(_normal),uv(_uv) {}

    vec3 position;
    vec3 normal;
    vec2 uv;
};
Cube::Cube(Shader shader, Material material): Component{shader,material}{
    vao = createVertexArrayObject();
}
GLuint Cube::createVertexArrayObject(){
    // Cube model
    // Cube model stolen from lab 3
    const TexturedColoredVertex texturedCubeVertexArray[] = {  // position,
            TexturedColoredVertex(vec3(-0.5f,-0.5f,-0.5f),vec3(-1.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f)), //left - red
            TexturedColoredVertex(vec3(-0.5f,-0.5f, 0.5f),vec3(-1.0f, 0.0f, 0.0f),vec2(0.0f, 1.0f)),
            TexturedColoredVertex(vec3(-0.5f, 0.5f, 0.5f), vec3(-1.0f, 0.0f, 0.0f),vec2(1.0f, 1.0f)),

            TexturedColoredVertex(vec3(-0.5f,-0.5f,-0.5f), vec3(-1.0f, 0.0f, 0.0f),vec2(0.0f, 0.0f)),
            TexturedColoredVertex(vec3(-0.5f, 0.5f, 0.5f), vec3(-1.0f, 0.0f, 0.0f),vec2(1.0f, 1.0f)),
            TexturedColoredVertex(vec3(-0.5f, 0.5f,-0.5f), vec3(-1.0f, 0.0f, 0.0f),vec2(1.0f, 0.0f)),

            TexturedColoredVertex(vec3( 0.5f, 0.5f,-0.5f), vec3( 0.0f, 0.0f,-1.0f),vec2(1.0f, 1.0f)), // far - blue
            TexturedColoredVertex(vec3(-0.5f,-0.5f,-0.5f), vec3( 0.0f, 0.0f,-1.0f),vec2(0.0f, 0.0f)),
            TexturedColoredVertex(vec3(-0.5f, 0.5f,-0.5f), vec3( 0.0f, 0.0f,-1.0f),vec2(0.0f, 1.0f)),

            TexturedColoredVertex(vec3( 0.5f, 0.5f,-0.5f), vec3( 0.0f, 0.0f,-1.0f),vec2(1.0f, 1.0f)),
            TexturedColoredVertex(vec3( 0.5f,-0.5f,-0.5f), vec3( 0.0f, 0.0f,-1.0f),vec2(1.0f, 0.0f)),
            TexturedColoredVertex(vec3(-0.5f,-0.5f,-0.5f), vec3( 0.0f, 0.0f,-1.0f),vec2(0.0f, 0.0f)),

            TexturedColoredVertex(vec3( 0.5f,-0.5f, 0.5f), vec3( 0.0f,-1.0f, 0.0f),vec2(1.0f, 1.0f)), // bottom - turquoise
            TexturedColoredVertex(vec3(-0.5f,-0.5f,-0.5f), vec3( 0.0f,-1.0f, 0.0f),vec2(0.0f, 0.0f)),
            TexturedColoredVertex(vec3( 0.5f,-0.5f,-0.5f), vec3( 0.0f,-1.0f, 0.0f),vec2(1.0f, 0.0f)),

            TexturedColoredVertex(vec3( 0.5f,-0.5f, 0.5f),vec3( 0.0f,-1.0f, 0.0f), vec2(1.0f, 1.0f)),
            TexturedColoredVertex(vec3(-0.5f,-0.5f, 0.5f), vec3( 0.0f,-1.0f, 0.0f),vec2(0.0f, 1.0f)),
            TexturedColoredVertex(vec3(-0.5f,-0.5f,-0.5f), vec3( 0.0f,-1.0f, 0.0f),vec2(0.0f, 0.0f)),

            TexturedColoredVertex(vec3(-0.5f, 0.5f, 0.5f),vec3( 0.0f, 0.0f, 1.0f), vec2(0.0f, 1.0f)), // near - green
            TexturedColoredVertex(vec3(-0.5f,-0.5f, 0.5f),vec3( 0.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f)),
            TexturedColoredVertex(vec3( 0.5f,-0.5f, 0.5f), vec3( 0.0f, 0.0f, 1.0f),vec2(1.0f, 0.0f)),

            TexturedColoredVertex(vec3( 0.5f, 0.5f, 0.5f), vec3( 0.0f, 0.0f, 1.0f),vec2(1.0f, 1.0f)),
            TexturedColoredVertex(vec3(-0.5f, 0.5f, 0.5f), vec3( 0.0f, 0.0f, 1.0f),vec2(0.0f, 1.0f)),
            TexturedColoredVertex(vec3( 0.5f,-0.5f, 0.5f), vec3( 0.0f, 0.0f, 1.0f),vec2(1.0f, 0.0f)),

            TexturedColoredVertex(vec3( 0.5f, 0.5f, 0.5f), vec3( 1.0f, 0.0f, 0.0f),vec2(1.0f, 1.0f)), // right - purple
            TexturedColoredVertex(vec3( 0.5f,-0.5f,-0.5f), vec3( 1.0f, 0.0f, 0.0f),vec2(0.0f, 0.0f)),
            TexturedColoredVertex(vec3( 0.5f, 0.5f,-0.5f), vec3( 1.0f, 0.0f, 0.0f),vec2(1.0f, 0.0f)),

            TexturedColoredVertex(vec3( 0.5f,-0.5f,-0.5f), vec3( 1.0f, 0.0f, 0.0f),vec2(0.0f, 0.0f)),
            TexturedColoredVertex(vec3( 0.5f, 0.5f, 0.5f),vec3( 1.0f, 0.0f, 0.0f), vec2(1.0f, 1.0f)),
            TexturedColoredVertex(vec3( 0.5f,-0.5f, 0.5f),vec3( 1.0f, 0.0f, 0.0f), vec2(0.0f, 1.0f)),

            TexturedColoredVertex(vec3( 0.5f, 0.5f, 0.5f),vec3( 0.0f, 1.0f, 0.0f), vec2(1.0f, 1.0f)), // top - yellow
            TexturedColoredVertex(vec3( 0.5f, 0.5f,-0.5f), vec3( 0.0f, 1.0f, 0.0f),vec2(1.0f, 0.0f)),
            TexturedColoredVertex(vec3(-0.5f, 0.5f,-0.5f), vec3( 0.0f, 1.0f, 0.0f),vec2(0.0f, 0.0f)),

            TexturedColoredVertex(vec3( 0.5f, 0.5f, 0.5f), vec3( 0.0f, 1.0f, 0.0f),vec2(1.0f, 1.0f)),
            TexturedColoredVertex(vec3(-0.5f, 0.5f,-0.5f),vec3( 0.0f, 1.0f, 0.0f), vec2(0.0f, 0.0f)),
            TexturedColoredVertex(vec3(-0.5f, 0.5f, 0.5f),vec3( 0.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f))
    };
    // Create a vertex array
    GLuint vertexArrayObject;
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);
    // Upload Vertex Buffer to the GPU, keep a reference to it (vertexBufferObject)
    GLuint vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texturedCubeVertexArray), texturedCubeVertexArray, GL_STATIC_DRAW);

    glVertexAttribPointer(0,                   // attribute 0 matches aPos in Vertex Shader
                          3,                   // size
                          GL_FLOAT,            // type
                          GL_FALSE,            // normalized?
                          sizeof(TexturedColoredVertex), // stride - each vertex contain 2 vec3 (position, color)
                          (void*)0             // array buffer offset
    );
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1,                            // attribute 2 matches aUV in Vertex Shader
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(TexturedColoredVertex),
                          (void*)(1*sizeof(vec3))      // uv is offseted by 2 vec3 (comes after position and color)
    );
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2,                            // attribute 2 matches aUV in Vertex Shader
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(TexturedColoredVertex),
                          (void*)(2*sizeof(vec3))      // uv is offseted by 2 vec3 (comes after position and color)
    );
    glEnableVertexAttribArray(2);

    return vertexArrayObject;
}

void Cube::Draw(Transform world, Transform entity, int mode){
    // set transform to mat4(1.0)
    glm::mat4 modelWorldMatrix = mat4(1.0f);
    transform.transformation = mat4(1.0);
    // load textures
    if(material.isTextured) {
       //shaderProgram.setInt("textureSampler", 0);
       glActiveTexture(GL_TEXTURE0+0);
       glBindTexture(GL_TEXTURE_2D, material.diffuseMapId);
       shaderProgram.setBool("material.isTextured", true);
        // Set our Texture sampler to user Texture Unit 0
    }
    // load the proper vao
    glBindVertexArray(vao);
    //glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // set the color
    shaderProgram.setVec3("material.color", material.vertexColor.x, material.vertexColor.y, material.vertexColor.z);
    // setup transform
    transform.transformation = translate(transform.transformation, transform.position);
    transform.transformation = transform.transformation * glm::mat4_cast(transform.rotation);
    transform.transformation = glm::scale(transform.transformation, transform.scaling);
    // matrix on the right applies first so we want to do the following
    modelWorldMatrix = world.transformation * entity.transformation * transform.transformation;
    shaderProgram.setMat4("worldMatrix", modelWorldMatrix);
    // draw a cube
    glDrawArrays(mode, 0, 36);
    shaderProgram.setBool("material.isTextured", false);
}