/* music.h -*-c-*-
 * In-game music handler.
 *
 * "THE BEER-WARE LICENCE" (Revision 42):
 * See the file LICENSE.md for details */

#ifndef MUSIC_h
#define MUSIC_h

#include <stdint.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include "config.h"

struct musicType {
    char *filename;
    const uint16_t samplingFrequency;
    const uint8_t numChannels;
    const uint16_t chunkSize;
};

typedef struct musicType music;

music *initMusic();

#endif
