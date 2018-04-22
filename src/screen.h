/** @file screen.h
 * @ingroup Screen
 */


#ifndef SCREEN_h
#define SCREEN_h

#define SCREEN_FULLSCREEN   0
#define SCREEN_WIDTH      800
#define SCREEN_HEIGHT     600

#include <SDL2/SDL.h>

/** @ingroup Screen
 */
struct ScreenType {
    SDL_Window *window;
};

typedef struct ScreenType Screen;

Screen *screenInit();
void screenTerminate(Screen *screen);

#endif
