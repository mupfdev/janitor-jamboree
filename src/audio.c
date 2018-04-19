/** @file audio.c
 * @ingroup   Audio
 * @defgroup  Audio
 * @brief     In-game music and sound effect handler
 * @author    Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 */

#include "audio.h"

/**
 * @brief   Initialise audio mixer.  See @ref struct mixerType.
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

/**
 * @brief   Initialise music structure.  See @ref struct musicType. 
 * @return  A pointer to a music structure, NULL on error.
 * @ingroup Audio
 */
music *musicInit()
{
    static music *tune;
    tune = malloc(sizeof(struct musicType));

    // Set default values.
    tune->filename = "res/music/overworld theme.ogg";

    tune->mus = Mix_LoadMUS(tune->filename);
    if (NULL == tune->mus) {
        fprintf(stderr, "%s\n", Mix_GetError());
        return NULL;
    }

    return tune;
}

/**
 * @brief   Play initialised music structure.
 * @param   tune An initialised music structure.  See @ref struct musicType.
 * @return  0 on success, -1 on error.
 * @ingroup Audio
 */
int8_t musicPlay(music *tune)
{
    if (-1 == Mix_PlayMusic(tune->mus, -1)) {
        fprintf(stderr, "%s\n", Mix_GetError());
        return -1;
    }

    return 0;
}

/**
 * @brief   Play initialised music structure with additional fade-in effect.
 *          See @ref struct muscType.
 * @param   tune An initialised music file.  See @ref struct musicType. 
 * @param   ms Time to fade-in the music in milliseconds.
 * @return  0 on success, -1 on error.
 * @ingroup Audio
 */
int8_t musicFadeIn(music *tune, uint16_t ms)
{
    if (-1 == Mix_FadeInMusic(tune->mus, -1, ms))
    {
        fprintf(stderr, "%s\n", Mix_GetError());
        return -1;
    }

    return 0;
}

/**
 * @brief   Terminate audio mixers.
 * @param   mix The mixer structure.  See @ref struct mixerType.
 * @ingroup Audio
 */
void mixerTerminate(mixer *mix)
{
    free(mix);
    Mix_CloseAudio();
    while(Mix_Init(0)) Mix_Quit();
}

/**
 * @brief   Terminate music file.
 * @param   tune The music structure.  See @ref struct musicType.
 * @ingroup Audio
 */
void musicTerminate(music *tune)
{
    free(tune);
    Mix_FreeMusic(tune->mus);
}
