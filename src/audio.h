#ifndef __AUDIO_H__
#define __AUDIO_H__

#ifndef __USE_OPENAL__
#define __USE_OPENAL__
#endif


#define CHANNELS_MUSIC  1
#define CHANNELS_SFX    15


#ifdef __USE_OPENAL__
#include <AL/al.h>
#include <AL/alc.h>
#endif /* __USE_OPENAL__ */

class sound;

#define SOUND_TYPE_MUSIC 0
#define SOUND_TYPE_SFX   1

class audio {
    public:
        audio();
        ~audio();

        int play(sound *s, int channel);
        void playSound(sound *s, int channel);
        void stopSound(int channel);

    private:

#ifdef __USE_OPENAL__
        ALCdevice *al_device;
        ALCcontext *al_context;
#endif /* __USE_OPENAL__ */

        unsigned int channels[CHANNELS_MUSIC+CHANNELS_SFX];

};

#endif /* __AUDIO_H__ */
