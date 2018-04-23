/** @file input.c
 * @ingroup   Input
 * @defgroup  Input
 * @brief     Input related functions, e.g. keyboard input.
 * @author    Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 */

#include "input.h"

/**
 * @brief   
 * @return  
 * @ingroup Input
 */
Input *inputInit()
{
    static Input *input;
    input = malloc(sizeof(struct InputType));

    return input;
}

/**
 * @brief   
 * @param   input
 * @return  
 * @ingroup Input
 */
int8_t inputLoop(Input *input)
{
    SDL_PumpEvents();
    if (SDL_PeepEvents(0, 0, SDL_PEEKEVENT, SDL_QUIT, SDL_QUIT) > 0)
        return -1;    

    input->keyState = SDL_GetKeyboardState(NULL);

    return 0;
}

/**
 * @brief   
 * @param   input
 * @ingroup Input
 */
void inputTerminate(Input *input)
{
    free(input);
}
