/* player.h -*-c-*-
 * Everything related to the game's player entity.
 *
 * "THE BEER-WARE LICENCE" (Revision 42):
 * See the file LICENSE.md for details */

#ifndef PLAYER_h
#define PLAYER_h

#define DIRECTION_UP    0
#define DIRECTION_DOWN  128
#define DIRECTION_LEFT  64
#define DIRECTION_RIGHT 192

#include <stdint.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "input.h"

struct playerData {
    const char *file;
    SDL_Surface *sprite;
    uint8_t direction;
    uint8_t inMotion;
    uint16_t frame;
    uint8_t refreshCounter;
    uint8_t refreshRate;
};

typedef struct playerData player;

player *playerInit();

int8_t playerUpdate(
    SDL_Surface *screen, input *controls,
    uint16_t screenWidth, uint16_t screenHeight,
    player *plr
);

#endif
