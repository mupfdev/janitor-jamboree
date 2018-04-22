/** @file player.c
 * @ingroup   Player
 * @defgroup  Player
 * @brief     Everything related to the game's hero.
 * @author    Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 */

#include "player.h"

/**
 * @brief 
 * @param plr
 * @return 
 * @ingroup Player
 */
static int32_t frameUpdate(void *plr)
{
    Player *player = (Player *)plr;

    while(player->threadIsRunning)
    {
        if (player->inMotion)
        {
            usleep(1000000 / player->fps);
            player->frame++;
        }
        else
            player->frame = 0;

        (9 <= player->frame) && (player->frame = 0);
    }

    return 0;
}

/**
 * @brief   
 * @return  
 * @ingroup Player
 */
Player *playerInit()
{
    static Player *player;
    player = malloc(sizeof(struct PlayerType));

    player->direction = DIRECTION_DOWN;
    player->inMotion  = 0;
    player->fps       = 24;
    player->frame     = 0;

    player->threadIsRunning = 1;
    player->frameUpdate = SDL_CreateThread(frameUpdate, "frameUpdate", player);
    if (NULL == player->frameUpdate)
    {
        fprintf(stderr, "%s\n", SDL_GetError());
        return NULL;
    }

    return player;
}

/**
 * @brief 
 * @param   player
 * @param   keyState
 * @return 
 * @ingroup Player
 */
uint8_t playerLoop(Player *player, const uint8_t *keyState)
{
    // Reset inMotion state (in case no key is pressed).
    player->inMotion = 0;

    if ((keyState[SDL_SCANCODE_LCTRL]) && (keyState[SDL_SCANCODE_Q]))
        return 0;

    if (keyState[SDL_SCANCODE_W])
    {
        player->direction = DIRECTION_UP;
        player->inMotion = 1;
        player->posY--;
    }

    if (keyState[SDL_SCANCODE_S])
    {
        player->direction = DIRECTION_DOWN;
        player->inMotion = 1;
        player->posY++;
    }

    if (keyState[SDL_SCANCODE_A])
    {
        player->direction = DIRECTION_LEFT;
        player->inMotion = 1;
        player->posX--;
    }

    if (keyState[SDL_SCANCODE_D])
    {
        player->direction = DIRECTION_RIGHT;
        player->inMotion = 1;
        player->posX++;
    }

    if (player->posX <= 0)     player->posX = 0;
    if (player->posX >= 65535) player->posX = 65535;
    if (player->posY <= 0)     player->posY = 0;
    if (player->posY >= 65535) player->posY = 65535;

    return 1;
}

/**
 * @brief   
 * @param   player
 * @return  
 * @ingroup Player
 */
int8_t playerReloadSprite(Player *player)
{
    player->sprite = IMG_Load(player->filename);

    if (NULL == player->sprite)
    {
        fprintf(stderr, "Couldn't load image: %s\n", IMG_GetError());
        return -1;
    }

    return 0;
}

/**
 * @brief   
 * @param   player
 * @ingroup Player
 */
void playerTerminate(Player *player)
{
    player->threadIsRunning = 0;
    SDL_WaitThread(player->frameUpdate, NULL);
    free(player);
    SDL_FreeSurface(player->sprite);
}
