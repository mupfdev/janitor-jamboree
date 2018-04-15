/* player.h -*-c-*-
 * Everything related to the game's player entity.
 *
 * "THE BEER-WARE LICENCE" (Revision 42):
 * See the file LICENSE.md for details */

#ifndef PLAYER_h
#define PLAYER_h

#define UP    0
#define DOWN  128
#define LEFT  64
#define RIGHT 192

#include <stdint.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

struct playerInfo {
    const char *file;
    SDL_Surface *sprite;
    uint8_t direction;
    uint16_t frame;
};

typedef struct playerInfo player;

player *playerInit();

int8_t playerRender(
    SDL_Surface *screen,
    uint16_t screenWidth, uint16_t screenHeight,
    player *player
);

#endif
