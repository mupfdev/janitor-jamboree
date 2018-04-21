/** @file audio.c
 * @ingroup   Audio
 * @defgroup  Audio
 * @brief     In-game music and sound effect handler.
 * @author    Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 */

#include "audio.h"

/**
 * @brief   Initialise audio mixer.  See @ref struct mixerType.
 * @return  A pointer to a Mixer, NULL on error.
 * @ingroup Audio
 */
Mixer *mixerInit()
{
    static Mixer *mixer;
    mixer = malloc(sizeof(struct mixerType));

    if (-1 == SDL_Init(SDL_INIT_AUDIO))
    {
        fprintf(stderr, "Couldn't initialise SDL: %s\n", SDL_GetError());
        return NULL;
    }

    // Set default values.
    mixer->audioFormat       = MIX_DEFAULT_FORMAT;
    mixer->flags             = MIX_INIT_OGG;
    mixer->bitmask           = Mix_Init(mixer->flags);
    mixer->chunkSize         = 4096;
    mixer->flags             = MIX_INIT_OGG;
    mixer->numChannels       = 2;
    mixer->samplingFrequency = 44100;

    if (mixer->flags != (mixer->bitmask & mixer->flags))
    {
        fprintf(stderr, "%s", Mix_GetError());
        return NULL;
    }

    if (-1 ==
        Mix_OpenAudio(
            mixer->samplingFrequency,
            mixer->audioFormat,
            mixer->numChannels,
            mixer->chunkSize))
    {
        fprintf(stderr, "%s\n", Mix_GetError());
        return NULL;
    }

    return mixer;
}

/**
 * @brief   Initialise Music structure.  See @ref struct musicType. 
 * @return  A pointer to a Music structure, NULL on error.
 * @ingroup Audio
 */
Music *musicInit()
{
    static Music *music;
    music = malloc(sizeof(struct musicType));

    // Set default values.
    music->filename = "res/music/overworld theme.ogg";

    music->mus = Mix_LoadMUS(music->filename);
    if (NULL == music->mus) {
        fprintf(stderr, "%s\n", Mix_GetError());
        return NULL;
    }

    return music;
}

/**
 * @brief   Play initialised Music structure.
 * @param   tune An initialised Music structure.  See @ref struct musicType.
 * @return  0 on success, -1 on error.
 * @ingroup Audio
 */
int8_t musicPlay(Music *music)
{
    if (-1 == Mix_PlayMusic(music->mus, -1)) {
        fprintf(stderr, "%s\n", Mix_GetError());
        return -1;
    }

    return 0;
}

/**
 * @brief   Play initialised Music structure with additional fade-in effect.
 *          See @ref struct musicType.
 * @param   tune An initialised Music file.  See @ref struct musicType. 
 * @param   ms Time to fade-in the music in milliseconds.
 * @return  0 on success, -1 on error.
 * @ingroup Audio
 */
int8_t musicFadeIn(Music *music, uint16_t ms)
{
    if (-1 == Mix_FadeInMusic(music->mus, -1, ms))
    {
        fprintf(stderr, "%s\n", Mix_GetError());
        return -1;
    }

    return 0;
}

/**
 * @brief   Terminate audio mixers.
 * @param   mix The Mixer structure.  See @ref struct mixerType.
 * @ingroup Audio
 */
void mixerTerminate(Mixer *mixer)
{
    free(mixer);
    Mix_CloseAudio();
    while(Mix_Init(0)) Mix_Quit();
}

/**
 * @brief   Terminate music file.
 * @param   tune The Music structure.  See @ref struct musicType.
 * @ingroup Audio
 */
void musicTerminate(Music *music)
{
    free(music);
    Mix_FreeMusic(music->mus);
}
