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
struct PlayerType {
    const char *filename;
    uint8_t    direction;
    uint8_t    flags;
    uint8_t    fps;
    uint16_t   frame;
    SDL_Thread *frameUpdate;
    uint8_t    threadIsRunning;
    int32_t    mapPosX;
    int32_t    mapPosY;
};

typedef struct PlayerType Player;

Player *playerInit();
void   playerLoadSprite(Player *player, const char *filename);
int8_t playerLoop(Player *player, const uint8_t *keyState);
void   playerTerminate(Player *player);

#endif
