//
// Created by Steven Smith on 2020-04-04.
// A class created to help and simplify the main driver into something more simple
// and easier to manage. A singleton instance that would keep references to important objects such as
// the currently active Shader
//

#ifndef INC_371PROCEDURALFOREST_RENDERER_H
#define INC_371PROCEDURALFOREST_RENDERER_H



// Include GLEW - OpenGL Extension Wrangler
#define GLEW_STATIC 1
#include <GL/glew.h>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "Shader.h"
class Renderer
{
public:
    Renderer();
    static void Initialize();
    static void Shutdown();
    static void BeginFrame();
    static void EndFrame();
private:


};


#endif //INC_371PROCEDURALFOREST_RENDERER_H
