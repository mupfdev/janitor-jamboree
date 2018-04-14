/* screen.c -*-c-*-
 * Screen/Window handler.
 *
 * "THE BEER-WARE LICENCE" (Revision 42):
 * See the file LICENSE.md for details */

#ifndef SCREEN_h
#define SCREEN_h

#include <stdint.h>
#include <SDL_getenv.h>
#include <SDL/SDL.h>

SDL_Surface *screenInit(
    uint16_t width, uint16_t height, uint8_t fullscreen,
    const char *title
);

void screenTerminate();

int8_t screenDrawPixel(
    SDL_Surface *surface,
    uint16_t x, uint16_t y,
    uint8_t r, uint8_t g, uint8_t b
);

#endif
