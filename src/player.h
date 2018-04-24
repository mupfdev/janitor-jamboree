/** @file player.h
 * @ingroup Player
 */

#ifndef PLAYER_h
#define PLAYER_h

#define DIRECTION_UP    0
#define DIRECTION_DOWN  128
#define DIRECTION_LEFT  64
#define DIRECTION_RIGHT 192

// Flags.
#define IN_MOTION   0
#define SPRITE_LOCK 1

#include <SDL2/SDL.h>

/** @ingroup Player
 */
typedef struct player_t {
    const char *filename;
    uint8_t    direction;
    uint8_t    flags;
    uint8_t    fps;
    uint16_t   frame;
    SDL_Thread *frameUpdate;
    uint8_t    threadIsRunning;
    int16_t    mapPosX;
    int16_t    mapPosY;
    // Logical player position:
    int16_t    posX;
    int16_t    posY;
    uint16_t   test1;
    uint16_t   test2;
} Player;

Player *playerInit();
void   playerLoadSprite(Player *player, const char *filename);
int8_t playerLoop(Player *player, const uint8_t *keyState);
void   playerTerminate(Player *player);

#endif
