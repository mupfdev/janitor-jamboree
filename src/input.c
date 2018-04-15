/* input.c -*-c-*-
 * Input handler.
 *
 * "THE BEER-WARE LICENCE" (Revision 42):
 * See the file LICENSE.md for details */

#include "input.h"

input *inputInit()
{
    static input *controls;
    controls = malloc(sizeof(struct inputData));

    if (-1 == SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL))
    {
        fprintf(stderr, "Couldn't set keyboard repeat rate: %s\n", SDL_GetError());
        return NULL;
    }

    return controls;
}

int8_t inputGetKeys(input *controls)
{
    SDL_Event event;
    SDL_PollEvent(&event);

    controls->state = SDL_GetKeyState(NULL);

    return 0;
}
