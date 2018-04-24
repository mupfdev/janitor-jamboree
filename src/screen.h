/** @file screen.h
 * @ingroup Screen
 */

#ifndef SCREEN_h
#define SCREEN_h

#include <SDL2/SDL.h>
#include "config.h"

/** @ingroup Screen
 */
typedef struct screen_t {
    SDL_Window *window;
} Screen;

Screen *screenInit();
void   screenTerminate(Screen *screen);

#endif
