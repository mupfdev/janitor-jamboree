/** @file screen.h
 * @ingroup Screen
 */

#ifndef SCREEN_h
#define SCREEN_h

#include <stdint.h>
#include <SDL_getenv.h>
#include <SDL/SDL.h>

SDL_Surface *screenInit(
    uint16_t width,
    uint16_t height,
    uint8_t  fullscreen,
    const char *title);

int8_t screenDrawPixel(
    SDL_Surface *surface,
    uint16_t x,
    uint16_t y,
    uint8_t  r,
    uint8_t  g,
    uint8_t  b);

void screenTerminate();

#endif
