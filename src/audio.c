/** @file audio.c
 * @ingroup   Audio
 * @defgroup  Audio
 * @brief     In-game music and sound effect handler
 * @author    Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 */

#include "audio.h"

/**
 * @brief   Initialise an audio mixer.
 * @return  A pointer to a mixer, NULL on error.
 * @ingroup Audio
 */
mixer *mixerInit()
{
    static mixer *mix;
    mix = malloc(sizeof(struct mixerType));

    if (-1 == SDL_Init(SDL_INIT_AUDIO))
    {
        fprintf(stderr, "Couldn't initialise SDL: %s\n", SDL_GetError());
        return NULL;
    }

    // Set default values.
    mix->audioFormat       = MIX_DEFAULT_FORMAT;
    mix->flags             = MIX_INIT_OGG;
    mix->bitmask           = Mix_Init(mix->flags);
    mix->chunkSize         = 4096;
    mix->flags             = MIX_INIT_OGG;
    mix->numChannels       = 2;
    mix->samplingFrequency = 44100;

    if (mix->flags != (mix->bitmask & mix->flags))
    {
        fprintf(stderr, "%s", Mix_GetError());
        return NULL;
    }

    if (-1 ==
        Mix_OpenAudio(
            mix->samplingFrequency,
            mix->audioFormat,
            mix->numChannels,
            mix->chunkSize))
    {
        fprintf(stderr, "%s\n", Mix_GetError());
        return NULL;
    }

    return mix;
}

/*
music *musicInit(char *filename)
{
    static music *tune;
    tune = malloc(sizeof(struct musicType));

    return tune;
}

int8_t musicPlay(music *tune)
{
    return 0;
}

int8_t musicPause(music *tune)
{
    return 0;
}

int8_t musicStop(music *tune)
{
    return 0;
}*/

/**
 * @brief Terminate audio mixers.
 * @ingroup Audio
 */
void mixerTerminate()
{
    Mix_CloseAudio();
    while(Mix_Init(0)) Mix_Quit();
}

/*void musicTerminate(music *tune)
{

}
*/