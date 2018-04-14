/* player.h -*-c-*-
 * Everything related to the game's player entity.
 *
 * "THE BEER-WARE LICENCE" (Revision 42):
 * See the file LICENSE.md for details */

#ifndef PLAYER_h
#define PLAYER_h

#define UP    0
#define DOWN  1
#define LEFT  2
#define RIGHT 3

#include <stdint.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

struct player {
    const char *file;
    SDL_Surface *sprite;
    uint8_t direction;
};

struct player *playerInit();

int8_t playerRender(
    SDL_Surface *screen,
    uint16_t screenWidth, uint16_t screenHeight,
    struct player *player
);

#endif
