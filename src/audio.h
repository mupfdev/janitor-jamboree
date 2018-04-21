/** @file audio.h
 * @ingroup Audio
 */

#ifndef AUDIO_h
#define AUDIO_h

#include <stdint.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include "config.h"

/**
 * @ingroup Audio
 */
struct mixerType {
    uint16_t audioFormat;
    int32_t  bitmask;
    uint16_t chunkSize;
    int32_t  flags;
    uint8_t  numChannels;
    uint16_t samplingFrequency;
};

struct musicType {
    char      *filename;
    Mix_Music *mus;
};

typedef struct mixerType Mixer;
typedef struct musicType Music;

Mixer *mixerInit();
Music *musicInit();
int8_t musicPlay(Music *music);
int8_t musicFadeIn(Music *music, uint16_t ms);

void mixerTerminate(Mixer *mixer);
void musicTerminate(Music *music);

#endif
