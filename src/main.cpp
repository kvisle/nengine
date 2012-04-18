#include <iostream>
#include <SDL.h>

#include "gl.h"
/*#include <GL/glew.h>
#include <GL/gl.h>*/

#include "game.h"
#include "input.h"

int main(int argc, char *argv[])
{
    int done = 0;

#ifdef __WIN32__
    freopen("stdout.txt","w",stdout);
#endif
    if (SDL_Init (SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "Unable to initialize SDL:" << SDL_GetError () << std::endl;

        return EXIT_FAILURE;
    }


//    SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 1);
    SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER, 1);
    SDL_Surface *s = SDL_SetVideoMode(960, 640, 24, SDL_OPENGL);

    glViewport (0, 0, 960, 640);

    game g;

    int ld = 0;

    while (!done)
    {
        SDL_Event e;
        union ninput in;
        while(SDL_PollEvent(&e))
        {
            switch(e.type)
            {
            case SDL_QUIT:
                done++;
                break;
            case SDL_KEYDOWN:
                in.type = NINPUT_KEYDOWN;
                in.key.sym = e.key.keysym.sym;
                g.in->read_input(in);

                g.in->keys[e.key.keysym.sym] = 1;

                if ( e.key.keysym.sym == 'r' ) {
                    g.setReload(true);
                }
                break;
            case SDL_KEYUP:
                in.type = NINPUT_KEYUP;
                in.key.sym = e.key.keysym.sym;
                g.in->read_input(in);

                g.in->keys[e.key.keysym.sym] = 0;
                break;
            }
        }

        g.update();
        g.render();

        int t = (1000/60)-(SDL_GetTicks()-ld);
        if ( t > 0 && t < 1000 ) SDL_Delay(t);
        ld = SDL_GetTicks();

    }

    return 0;
    (void)s;
    (void)argc;
    (void)argv;
}
