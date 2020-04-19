//
// Created by Steven Smith(4 on 2020-04-05.
// Created for Comp 371 Concordia W 2020 Procedural Generation project
//
// Modified by RemineralizedWater(Michael Rowe) on 2020-04-08
// Student ID: 26101267
//

/*
 * An extension of the super class Entity used to render the World through simplified commands
 * Also contains functions that enables the instanced drawing. A single tree can contain from
 * 100 - 1000 cubes. As such the traditional draw technique is not sufficient as it will significantly
 * slow down the generations of the trees.
 *
 */
#include <World.h>
#include "Tree.h"

void Tree::Draw() {
    /*
     * Instance drawing no need to setup anything TreeGenerator should do that for us. Using one VAO
     * and using instancing
     */
    glm::mat4 modelWorldMatrix = mat4(1.0f);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, leaves.diffuseMapId);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, trunk.diffuseMapId);
    Renderer::getCurrentShader()->setBool("material.isTextured", true);
    Renderer::getCurrentShader()->setInt("material.diffuseMap[1]", 0);
    Renderer::getCurrentShader()->setInt("material.diffuseMap[0]", 2);
    // Set our Texture sampler to user Texture Unit 0

    // load the proper vao
    glBindVertexArray(vao);
    //glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // set the color
   // Renderer::getCurrentShader()->setVec3("material.color", cube->getMaterial().vertexColor.x, cube->getMaterial().vertexColor.y, cube->getMaterial().vertexColor.z);
    // setup transform
    transform->transformation = mat4(1.0);
    transform->transformation = translate(transform->transformation, transform->position);
    transform->transformation = transform->transformation * glm::mat4_cast(transform->rotation);
    transform->transformation = glm::scale(transform->transformation, transform->scaling);
    // matrix on the right applies first so we want to do the following
    modelWorldMatrix = World::getCurrent().getTransform().transformation* transform->transformation ;
    Renderer::getCurrentShader()->setMat4("worldMatrix", modelWorldMatrix);
    // draw a cube
    glDrawArraysInstanced(Renderer::getRenderMode(), 0, 36, offset.size());
    Renderer::getCurrentShader()->setBool("material.isTextured", false);
}

void Tree::Update() {

}
void Tree::addLeavesOffset(glm::vec3 l_offset) {
   offset.push_back(l_offset);
}


void Tree::removeLeavesOffset(int index) {
    offset.erase(offset.begin()+index);
}

void Tree::createVAO(){
    leaves.addTexture("../Assets/Textures/leaves_c4.png");
    trunk.addTexture("../Assets/Textures/tree.jpg");
    // Cube model
    // Cube model stolen from lab 3
    const TexturedColoredVertex texturedCubeVertexArray[] = {  // position,
            TexturedColoredVertex(transform->size * vec3(-0.5f,-0.5f,-0.5f),vec3(-1.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f)), //left - red
            TexturedColoredVertex(transform->size *vec3(-0.5f,-0.5f, 0.5f),vec3(-1.0f, 0.0f, 0.0f),vec2(0.0f, 1.0f)),
            TexturedColoredVertex(transform->size *vec3(-0.5f, 0.5f, 0.5f), vec3(-1.0f, 0.0f, 0.0f),vec2(1.0f, 1.0f)),

            TexturedColoredVertex(transform->size *vec3(-0.5f,-0.5f,-0.5f), vec3(-1.0f, 0.0f, 0.0f),vec2(0.0f, 0.0f)),
            TexturedColoredVertex(transform->size *vec3(-0.5f, 0.5f, 0.5f), vec3(-1.0f, 0.0f, 0.0f),vec2(1.0f, 1.0f)),
            TexturedColoredVertex(transform->size *vec3(-0.5f, 0.5f,-0.5f), vec3(-1.0f, 0.0f, 0.0f),vec2(1.0f, 0.0f)),

            TexturedColoredVertex(transform->size *vec3( 0.5f, 0.5f,-0.5f), vec3( 0.0f, 0.0f,-1.0f),vec2(1.0f, 1.0f)), // far - blue
            TexturedColoredVertex(transform->size *vec3(-0.5f,-0.5f,-0.5f), vec3( 0.0f, 0.0f,-1.0f),vec2(0.0f, 0.0f)),
            TexturedColoredVertex(transform->size *vec3(-0.5f, 0.5f,-0.5f), vec3( 0.0f, 0.0f,-1.0f),vec2(0.0f, 1.0f)),

            TexturedColoredVertex(transform->size *vec3( 0.5f, 0.5f,-0.5f), vec3( 0.0f, 0.0f,-1.0f),vec2(1.0f, 1.0f)),
            TexturedColoredVertex(transform->size *vec3( 0.5f,-0.5f,-0.5f), vec3( 0.0f, 0.0f,-1.0f),vec2(1.0f, 0.0f)),
            TexturedColoredVertex(transform->size *vec3(-0.5f,-0.5f,-0.5f), vec3( 0.0f, 0.0f,-1.0f),vec2(0.0f, 0.0f)),

            TexturedColoredVertex(transform->size *vec3( 0.5f,-0.5f, 0.5f), vec3( 0.0f,-1.0f, 0.0f),vec2(1.0f, 1.0f)), // bottom - turquoise
            TexturedColoredVertex(transform->size *vec3(-0.5f,-0.5f,-0.5f), vec3( 0.0f,-1.0f, 0.0f),vec2(0.0f, 0.0f)),
            TexturedColoredVertex(transform->size *vec3( 0.5f,-0.5f,-0.5f), vec3( 0.0f,-1.0f, 0.0f),vec2(1.0f, 0.0f)),

            TexturedColoredVertex(transform->size *vec3( 0.5f,-0.5f, 0.5f),vec3( 0.0f,-1.0f, 0.0f), vec2(1.0f, 1.0f)),
            TexturedColoredVertex(transform->size *vec3(-0.5f,-0.5f, 0.5f), vec3( 0.0f,-1.0f, 0.0f),vec2(0.0f, 1.0f)),
            TexturedColoredVertex(transform->size *vec3(-0.5f,-0.5f,-0.5f), vec3( 0.0f,-1.0f, 0.0f),vec2(0.0f, 0.0f)),

            TexturedColoredVertex(transform->size *vec3(-0.5f, 0.5f, 0.5f),vec3( 0.0f, 0.0f, 1.0f), vec2(0.0f, 1.0f)), // near - green
            TexturedColoredVertex(transform->size *vec3(-0.5f,-0.5f, 0.5f),vec3( 0.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f)),
            TexturedColoredVertex(transform->size *vec3( 0.5f,-0.5f, 0.5f), vec3( 0.0f, 0.0f, 1.0f),vec2(1.0f, 0.0f)),

            TexturedColoredVertex(transform->size *vec3( 0.5f, 0.5f, 0.5f), vec3( 0.0f, 0.0f, 1.0f),vec2(1.0f, 1.0f)),
            TexturedColoredVertex(transform->size *vec3(-0.5f, 0.5f, 0.5f), vec3( 0.0f, 0.0f, 1.0f),vec2(0.0f, 1.0f)),
            TexturedColoredVertex(transform->size *vec3( 0.5f,-0.5f, 0.5f), vec3( 0.0f, 0.0f, 1.0f),vec2(1.0f, 0.0f)),

            TexturedColoredVertex(transform->size *vec3( 0.5f, 0.5f, 0.5f), vec3( 1.0f, 0.0f, 0.0f),vec2(1.0f, 1.0f)), // right - purple
            TexturedColoredVertex(transform->size *vec3( 0.5f,-0.5f,-0.5f), vec3( 1.0f, 0.0f, 0.0f),vec2(0.0f, 0.0f)),
            TexturedColoredVertex(transform->size *vec3( 0.5f, 0.5f,-0.5f), vec3( 1.0f, 0.0f, 0.0f),vec2(1.0f, 0.0f)),

            TexturedColoredVertex(transform->size *vec3( 0.5f,-0.5f,-0.5f), vec3( 1.0f, 0.0f, 0.0f),vec2(0.0f, 0.0f)),
            TexturedColoredVertex(transform->size *vec3( 0.5f, 0.5f, 0.5f),vec3( 1.0f, 0.0f, 0.0f), vec2(1.0f, 1.0f)),
            TexturedColoredVertex(transform->size *vec3( 0.5f,-0.5f, 0.5f),vec3( 1.0f, 0.0f, 0.0f), vec2(0.0f, 1.0f)),

            TexturedColoredVertex(transform->size *vec3( 0.5f, 0.5f, 0.5f),vec3( 0.0f, 1.0f, 0.0f), vec2(1.0f, 1.0f)), // top - yellow
            TexturedColoredVertex(transform->size *vec3( 0.5f, 0.5f,-0.5f), vec3( 0.0f, 1.0f, 0.0f),vec2(1.0f, 0.0f)),
            TexturedColoredVertex(transform->size *vec3(-0.5f, 0.5f,-0.5f), vec3( 0.0f, 1.0f, 0.0f),vec2(0.0f, 0.0f)),

            TexturedColoredVertex(transform->size *vec3( 0.5f, 0.5f, 0.5f), vec3( 0.0f, 1.0f, 0.0f),vec2(1.0f, 1.0f)),
            TexturedColoredVertex(transform->size *vec3(-0.5f, 0.5f,-0.5f),vec3( 0.0f, 1.0f, 0.0f), vec2(0.0f, 0.0f)),
            TexturedColoredVertex(transform->size *vec3(-0.5f, 0.5f, 0.5f),vec3( 0.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f))
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
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,                   // attribute 0 matches aPos in Vertex Shader
                          3,                   // size
                          GL_FLOAT,            // type
                          GL_FALSE,            // normalized?
                          sizeof(TexturedColoredVertex), // stride - each vertex contain 2 vec3 (position, color)
                          (void*)0             // array buffer offset
    );

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,                            // attribute 2 matches aUV in Vertex Shader
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(TexturedColoredVertex),
                          (void*)(1*sizeof(vec3))      // uv is offseted by 2 vec3 (comes after position and color)
    );

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,                            // attribute 2 matches aUV in Vertex Shader
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(TexturedColoredVertex),
                          (void*)(2*sizeof(vec3))      // uv is offseted by 2 vec3 (comes after position and color)
    );

    glGenBuffers(1, &instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * offset.size(), &offset[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glEnableVertexAttribArray(3);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO); // this attribute comes from a different vertex buffer
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(3, 1); // tell OpenGL this is an instanced vertex attribute.

    glGenBuffers(1, &instanceTextVBO);
    glBindBuffer(GL_ARRAY_BUFFER, instanceTextVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * textureOffset.size(), &textureOffset[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glEnableVertexAttribArray(4);
    glBindBuffer(GL_ARRAY_BUFFER, instanceTextVBO); // this attribute comes from a different vertex buffer
    glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(int), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(4, 1); // tell OpenGL this is an instanced vertex attribute.

    vao = vertexArrayObject;
}
