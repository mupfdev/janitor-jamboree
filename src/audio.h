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
    char *filename;
};

typedef struct mixerType mixer;
typedef struct musicType music;

mixer *mixerInit();
music *musicInit(char *filename);
int8_t musicPlay(music *tune);
int8_t musicPause(music *tune);
int8_t musicStop(music *tune);

void mixerTerminate();
void musicTerminate(music *tune);

#endif
