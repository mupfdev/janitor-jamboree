/** @file screen.h
 * @ingroup Screen
 */

#ifndef SCREEN_h
#define SCREEN_h

#include <SDL2/SDL.h>

/** @ingroup Screen
 */
struct ScreenType {
    SDL_Window *window;
};

typedef struct ScreenType Screen;

Screen *screenInit(
    uint16_t width,
    uint16_t height,
    uint8_t  fullscreen,
    const char *title);

void screenTerminate(Screen *screen);

#endif
