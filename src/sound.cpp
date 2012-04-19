#include "game.h"
#include "sound.h"
#include "resource.h"
#include "audio.h"

#ifdef __USE_OPENAL__
#include <SDL.h>
#include <AL/al.h>
#include <AL/alc.h>
#endif /* __USE_OPENAL__ */

sound::sound(game *g, std::string filename)
{
    this->g = g;

    resource r(filename);

    loadWav(r.getRaw(), r.getLength());
}

void
sound::loadWav(const char * buffer, int length)
{
    puts("sound::loadWav");
#ifdef __USE_OPENAL__
/*
    Yes, I also use SDL.
*/
    SDL_AudioSpec spec;
    ALenum format = NULL;

    if ( SDL_LoadWAV_RW(SDL_RWFromMem((char *)buffer, length), 0, &spec, &buf, &(this->length)) == NULL )
    {
        fprintf(stderr, "Could not open thingie from memory: %s\n", SDL_GetError());
        return;
    }

    printf("this->buffer: %d\n", this->buffer);
    alGenBuffers(1, &(this->buffer));
    printf("this->buffer: %d\n", this->buffer);

    switch (spec.format) {
        case AUDIO_U8:
        case AUDIO_S8:
            format = (spec.channels==1) ? AL_FORMAT_MONO8 : AL_FORMAT_STEREO8;
            break;
        case AUDIO_U16LSB:
        case AUDIO_S16LSB:
            format = (spec.channels==1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
            break;
    }

    alBufferData(this->buffer, format, buf, this->length, spec.freq);

    printf("format: %d, length: %d, freq: %d\n", format, this->length, spec.freq);
    puts("Uploaded to buffer");
    if ( alGetError() != AL_NO_ERROR) 
        printf("load failed wat : %s\n", alGetError());
    printf("this->buffer: %d\n", this->buffer);

#endif /* __USE_OPENAL__ */
}

void
sound::play()
{
    printf("this->buffer: %d\n", this->buffer);

    g->a->play(this, SOUND_TYPE_SFX);
}
