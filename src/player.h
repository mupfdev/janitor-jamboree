/** @file player.h
 * @ingroup Player
 */

#ifndef PLAYER_h
#define PLAYER_h

#define _DEFAULT_SOURCE

#define DIRECTION_UP    0
#define DIRECTION_DOWN  128
#define DIRECTION_LEFT  64
#define DIRECTION_RIGHT 192

#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "config.h"

/** @ingroup Player
 */
struct PlayerType {
    const char  *file;
    SDL_Surface *sprite;
    uint8_t     direction;
    uint8_t     inMotion;
    uint8_t     fps;
    uint16_t    frame;
    SDL_Thread  *frameUpdateThread;
    uint16_t    posX;
    uint16_t    posY;
    uint8_t     threadIsRunning;
};

typedef struct PlayerType Player;

Player *playerInit();
int8_t playerReloadSprite(Player *player);
uint8_t playerUpdate(Player *player, config_t config, const uint8_t *keyState);
void playerTerminate(Player *player);

#endif
