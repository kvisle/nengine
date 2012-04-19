#ifndef __SOUND_H__
#define __SOUND_H__

#include <string>

#define __USE_OPENAL__

#ifdef __USE_OPENAL__
#include <SDL.h>
#endif

class game;

class sound {
    public:
        sound(game *g, std::string filename);

        void loadWav(const char * buffer, int length);
        void play();

#ifdef __USE_OPENAL__
        unsigned int length;
        Uint8 *buf;
        SDL_AudioSpec spec;
        unsigned int buffer;
#endif /* __USE_OPENAL__ */


    private:
        game *g;

};

#endif /* __SOUND_H__ */
