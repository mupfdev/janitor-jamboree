/** @file input.c
 * @ingroup   Input
 * @defgroup  Input
 * @brief     Input handler
 * @author    Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 */

#include "input.h"

/**
 * @brief 
 * @return 
 * @ingroup Input
 */
input *inputInit()
{
    static input *controls;
    controls = malloc(sizeof(struct inputType));

    if (-1 ==
        SDL_EnableKeyRepeat(
            SDL_DEFAULT_REPEAT_DELAY,
            SDL_DEFAULT_REPEAT_INTERVAL))
    {
        fprintf(stderr, "Couldn't set keyboard repeat rate: %s\n", SDL_GetError());
        return NULL;
    }

    controls->quit = 0;

    return controls;
}

/**
 * @brief 
 * @param controls
 * @ingroup Input
 */
void inputGetKeys(input *controls)
{
    SDL_Event event;
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT)
        controls->quit = 1;

    controls->keyState = SDL_GetKeyState(NULL);
}
