/** @file audio.c
 * @ingroup   Audio
 * @defgroup  Audio
 * @brief     Audio related functions, e.g. music, mixer, sound effects.
 * @author    Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 */

#include "audio.h"

/**
 * @brief   
 * @return  
 * @ingroup Audio
 */
Mixer *mixerInit()
{
    static Mixer *mixer;
    mixer = malloc(sizeof(struct MixerType));

    if (-1 == SDL_Init(SDL_INIT_AUDIO))
    {
        fprintf(stderr, "Couldn't initialise SDL: %s\n", SDL_GetError());
        free(mixer);
        return NULL;
    }

    mixer->audioFormat       = MIX_DEFAULT_FORMAT;
    mixer->chunkSize         = 4096;
    mixer->numChannels       = 2;
    mixer->samplingFrequency = 44100;

    if (-1 ==
        Mix_OpenAudio(
            mixer->samplingFrequency,
            mixer->audioFormat,
            mixer->numChannels,
            mixer->chunkSize))
    {   
        fprintf(stderr, "%s\n", Mix_GetError());
        free(mixer);
        return NULL;
    }

    return mixer;
}

/**
 * @brief   
 * @return  
 * @ingroup Audio
 */
Music *musicInit()
{
    static Music *music;
    music = malloc(sizeof(struct MusicType));

    return music;
}

/**
 * @brief   
 * @param   music
 * @return  
 * @ingroup Audio
 */
int8_t musicPlay(Music *music)
{
    music->mus = Mix_LoadMUS(music->filename);

    if (NULL == music->mus) {
        fprintf(stderr, "%s\n", Mix_GetError());
        return -1;
    }

    if (-1 == Mix_PlayMusic(music->mus, -1)) {
        fprintf(stderr, "%s\n", Mix_GetError());
        return -1;
    }

    return 0;
}

/**
 * @brief   
 * @param   music
 * @param   ms
 * @return  
 * @ingroup Audio
 */
int8_t musicFadeIn(Music *music, uint16_t ms)
{
    music->mus = Mix_LoadMUS(music->filename);

    if (NULL == music->mus) {
        fprintf(stderr, "%s\n", Mix_GetError());
        return -1;
    }

    if (-1 == Mix_FadeInMusic(music->mus, -1, ms))
    {
        fprintf(stderr, "%s\n", Mix_GetError());
        return -1;
    }

    return 0;
}

/**
 * @brief   
 * @param   mixer
 * @ingroup Audio
 */
void mixerTerminate(Mixer *mixer)
{
    free(mixer);
    Mix_CloseAudio();
    while(Mix_Init(0)) Mix_Quit();
}

/**
 * @brief   
 * @param   music
 * @ingroup Audio
 */
void musicTerminate(Music *music)
{
    free(music);
}
