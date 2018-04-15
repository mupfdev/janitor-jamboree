/* input.c -*-c-*-
 * Input handler.
 *
 * "THE BEER-WARE LICENCE" (Revision 42):
 * See the file LICENSE.md for details */

#include "input.h"

int8_t inputInit()
{
    if (-1 == SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL))
    {
        fprintf(stderr, "Couldn't set keyboard repeat rate: %s\n", SDL_GetError());
        return -1;
    }

    return 0;
}

uint32_t inputPollEvent()
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        SDL_keysym keysym;

        switch(event.type)
        {
            case SDL_QUIT:
                return SDL_QUIT;
            case SDL_KEYUP:
                return SDL_KEYUP;
            case SDL_KEYDOWN:
                keysym = event.key.keysym;
                return keysym.sym;
        }
    }

    return SDLK_UNKNOWN;
}
