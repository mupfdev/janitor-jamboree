/** @file player.h
 * @ingroup Player
 */

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
#include "config.h"

/** @ingroup Audio
 */
struct playerType {
    const char  *file;
    SDL_Surface *sprite;
    uint8_t   direction;
    uint8_t   inMotion;
    uint8_t   fps;
    uint16_t  frame;
    pthread_t frameUpdateThread;
    uint16_t  posX;
    uint16_t  posY;
};

typedef struct playerType player;

player *playerInit();
int8_t playerUpdate(player *plr, config_t config, uint8_t *keyState);
void playerTerminate(player *plr);

#endif
