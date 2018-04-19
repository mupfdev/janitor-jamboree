/** @file input.c
 * @ingroup   Input
 * @defgroup  Input
 * @brief     Input handler
 * @author    Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 */

#include "input.h"

/**
 * @brief   Initialise input structure.  See @ref struct inputType.
 * @return  A pointer to an input structure on success, NULL on error.
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
 * @brief   Get current key state.
 * @param   controls The input structure.  See @ref struct inputType.
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

/**
 * @brief Terminate input structure.
 * @param controls The input structure.  See @ref struct inputType.
 */
void inputTerminate(input *controls)
{
    free(controls);
}
