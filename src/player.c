/** @file player.c
 * @ingroup   Player
 * @defgroup  Player
 * @brief     Functions to handle the game's protagonist.
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
        if ((player->flags >> IN_MOTION) & 1)
        {
            SDL_Delay(1000 / player->fps);
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

    player->direction  = DIRECTION_DOWN;
    player->flags      = 0;
    player->fps        = 24;
    player->frame      = 0;
    player->mapPosX    = 0;
    player->mapPosY    = 0;

    player->threadIsRunning = 1;
    player->frameUpdate = SDL_CreateThread(frameUpdate, "frameUpdate", player);
    if (NULL == player->frameUpdate)
    {
        fprintf(stderr, "%s\n", SDL_GetError());
        free(player);
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
int8_t playerLoop(Player *player, const uint8_t *keyState)
{
    // Reset inMotion state (in case no key is pressed).
    player->flags &= ~(1 << IN_MOTION);

    if ((keyState[SDL_SCANCODE_LCTRL]) && (keyState[SDL_SCANCODE_Q]))
        return -1;

    if (keyState[SDL_SCANCODE_G])
    {
        if (strstr(player->filename, "female.png"))
            playerLoadSprite(player, "res/sprites/male.png");
        else
            playerLoadSprite(player, "res/sprites/female.png");
        SDL_Delay(200);
    }

    if (keyState[SDL_SCANCODE_W])
    {
        player->direction = DIRECTION_UP;
        player->flags |= 1 << IN_MOTION;
        player->mapPosY++;
    }

    if (keyState[SDL_SCANCODE_S])
    {
        player->direction = DIRECTION_DOWN;
        player->flags |= 1 << IN_MOTION;
        player->mapPosY--;
    }

    if (keyState[SDL_SCANCODE_A])
    {
        player->direction = DIRECTION_LEFT;
        player->flags |= 1 << IN_MOTION;
        player->mapPosX++;
    }

    if (keyState[SDL_SCANCODE_D])
    {
        player->direction = DIRECTION_RIGHT;
        player->flags |= 1 << IN_MOTION;
        player->mapPosX--;
    }

    return 0;
}

/**
 * @brief    
 * @param   player
 * @param   filename
 * @ingroup Player
 */
void playerLoadSprite(Player *player, const char *filename)
{
    player->filename  = filename;
    player->flags    &= ~(1 << SPRITE_LOCK);
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
}
