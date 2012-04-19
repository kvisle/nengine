#include <cstdio>
#include "audio.h"
#include "sound.h"

audio::audio()
{
#ifdef __USE_OPENAL__
    ALint attribs[4] = { 0, 0, 0, 0 };

    al_device = alcOpenDevice(NULL);

    if (al_device == NULL)
    {
        printf("OpenAL: No sound for you :( (Unable to open sound device)\n");
        return;
    }

    al_context = alcCreateContext( al_device, attribs );
    if (al_context == NULL)
    {
        printf("Unable to create OpenAL context\n");
        return;
    }

    alGetError();

    if ( alcMakeContextCurrent(al_context) == AL_FALSE )
    {
        printf("OpenAL: Failure to set default context - probably means no sound for you\n");
        return;
    }

    puts("Al didn't return any errors, you should be happy!");
    alGenSources(CHANNELS_MUSIC+CHANNELS_SFX, channels);
#endif /* __USE_OPENAL__ */
}

audio::~audio()
{

}

int
audio::play(sound *s, int type)
{
    printf("audio::play(%d)\n", type);
    int i;
    ALint val;

    int typemin, typemax;

    if ( type == SOUND_TYPE_MUSIC )
    {
        typemin = 0;
        typemax = CHANNELS_MUSIC;
    }
    else if ( type == SOUND_TYPE_SFX )
    {
        typemin = CHANNELS_MUSIC;
        typemax = typemin+CHANNELS_SFX;
    }
    else {
        return -1;
    }

    for(i=typemin;i<typemax;i++)
    {
        alGetSourcei(channels[i], AL_SOURCE_STATE, &val);
        if ( val == AL_PLAYING )
            continue;

        playSound(s, i);
        return i;
    }
    return -1;
}

void 
audio::playSound(sound *s, int channel)
{
    printf("playSound(%x, %d) - buffer: %d\n", s, channel, s->buffer);
#ifdef __USE_OPENAL__
    alSourcef(channels[channel], AL_GAIN, 0.2f);
    alSourcei(channels[channel], AL_BUFFER, s->buffer);
    alSourcei(channels[channel], AL_LOOPING, AL_FALSE);
    alSourcePlay(channels[channel]);
    if ( alGetError() != AL_NO_ERROR)
        printf("load failed wat : %d\n", alGetError());

    puts("Playing loop");
#endif
}

void 
audio::stopSound(int channel)
{
    puts("stopSound()");
#ifdef __USE_OPENAL__
    alSourceStop(channel);
    puts("Stopping loop");
#endif
}

