#include <iostream>
#include <SDL.h>

#include <GL/gl.h>

#include "game.h"


int main(int argc, char *argv[])
{
    int done = 0;

    if (SDL_Init (SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "Unable to initialize SDL:" << SDL_GetError () << std::endl;

        return EXIT_FAILURE;
    }


    SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 1);
    SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER, 1);
    SDL_Surface *s = SDL_SetVideoMode(960, 640, 24, SDL_OPENGL);

    glViewport (0, 0, 960, 640);

    game g;

    while (!done)
    {
        SDL_Event e;
        while(SDL_PollEvent(&e))
        {
            switch(e.type)
            {
            case SDL_QUIT:
                done++;
                break;
            }
        }

        g.update();
        g.render();
    }

    return 0;
    (void)s;
    (void)argc;
    (void)argv;
}
