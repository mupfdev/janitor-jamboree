/** @file audio.h
 * @ingroup Audio
 */

#ifndef AUDIO_h
#define AUDIO_h

#include <stdint.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "config.h"

/**
 * @ingroup Audio
 */
struct MixerType {
    uint16_t audioFormat;
    int32_t  bitmask;
    uint16_t chunkSize;
    int32_t  flags;
    uint8_t  numChannels;
    uint16_t samplingFrequency;
};

struct MusicType {
    char      *filename;
    Mix_Music *mus;
};

typedef struct MixerType Mixer;
typedef struct MusicType Music;

Mixer *mixerInit();
Music *musicInit();
int8_t musicPlay(Music *music);
int8_t musicFadeIn(Music *music, uint16_t ms);

void mixerTerminate(Mixer *mixer);
void musicTerminate(Music *music);

#endif
