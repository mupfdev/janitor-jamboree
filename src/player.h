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

#include <pthread.h>
#include <stdint.h>
#include <unistd.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

struct playerType {
    const char  *file;
    SDL_Surface *sprite;
    uint8_t  direction;
    uint8_t  inMotion;
    uint8_t  fps;
    uint8_t  fpsc;
    uint16_t frame;
};

typedef struct playerType player;

player *playerInit();

int8_t playerUpdate(
    SDL_Surface *screen,
    uint8_t  *keyState,
    uint8_t  quit,
    uint16_t screenWidth,
    uint16_t screenHeight,
    player   *plr);

void playerTerminate(player *plr);

#endif
