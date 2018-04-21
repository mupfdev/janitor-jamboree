/** @file input.c
 * @ingroup   Input
 * @defgroup  Input
 * @brief     Input handler.
 * @author    Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 */

#include "input.h"

/**
 * @brief   Initialise Input structure.  See @ref struct inputType.
 * @return  A pointer to an Input structure on success, NULL on error.
 * @ingroup Input
 */
Input *inputInit()
{
    static Input *input;
    input = malloc(sizeof(struct inputType));

    if (-1 ==
        SDL_EnableKeyRepeat(
            SDL_DEFAULT_REPEAT_DELAY,
            SDL_DEFAULT_REPEAT_INTERVAL))
    {
        fprintf(stderr, "Couldn't set keyboard repeat rate: %s\n", SDL_GetError());
        return NULL;
    }

    return input;
}

/**
 * @brief   Write current key state to Input structure.
 * @param   input The input structure.  See @ref struct inputType.
 * @return  1 or 0 when SDL_QUIT has been triggered.
 * @ingroup Input
 */
int8_t inputGetKeys(Input *input)
{
    SDL_Event event;
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT) return 0;

    input->keyState = SDL_GetKeyState(NULL);

    return 1;
}

/**
 * @brief Terminate Input structure.
 * @param input The Input structure.  See @ref struct inputType.
 */
void inputTerminate(Input *input)
{
    free(input);
}
