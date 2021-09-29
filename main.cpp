#include <iostream>
#include <vector>
#include <string>
#include "UMLClass.h"
#include "UMLController.h"
#include "UMLModel.h"
#include <SDL.h>
#include <SDL_opengl.h>


int main()
{

    UMLModel model;
    UMLController controller {model};
    controller.execute();
    
    
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Test with OPENGL",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, SDL_WINDOW_OPENGL);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    S   DL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GLContext context = SDL_GL_CreateContext(window);

    return 0;    
}

