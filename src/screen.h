/** @file screen.h
 * @ingroup Screen
 */

#ifndef SCREEN_h
#define SCREEN_h

#include <SDL2/SDL.h>
#include "config.h"

/** @ingroup Screen
 */
struct ScreenType {
    SDL_Window *window;
};

typedef struct ScreenType Screen;

Screen *screenInit();
void   screenTerminate(Screen *screen);

#endif
