/** @file input.c
 * @ingroup   Input
 * @defgroup  Input
 * @brief     Input handler.
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

    /*if (-1 == SDL_SetRelativeMouseMode(SDL_TRUE))
    {
        fprintf(stderr, "%s\n", SDL_GetError());
        return NULL;
    }*/

    return input;
}

/**
 * @brief   
 * @param   input
 * @return  
 * @ingroup Input
 */
uint8_t inputGetKeys(Input *input)
{   
    SDL_Event event;
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT) return 0;

    input->keyState = SDL_GetKeyboardState(NULL);

    return 1;
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
