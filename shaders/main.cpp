#include "sdl2/sdl.h"
#include <iostream>
#include <OpenGl/gl.h>


int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindow(
                     "",             // window title
                     SDL_WINDOWPOS_CENTERED,     // x position, centered
                     SDL_WINDOWPOS_CENTERED,     // y position, centered
                     640,                        // width, in pixels
                     480,                        // height, in pixels
                     SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE           // flags
                     );
    
    std::cout << "Windows in initialized...";
    
    SDL_Event e;
    bool quit = false;
    while (!quit){
        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                quit = true;
            }
            if (e.type == SDL_KEYDOWN){
                quit = true;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN){
                quit = true;
            }
        }
    }

    
    return 0;
}
