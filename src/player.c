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

    // Set default values.
    player->file   = "res/sprites/male.png";

    if (-1 == playerReloadSprite(player))
        return NULL;

    player->direction = DIRECTION_DOWN;
    player->inMotion  = 0;
    player->fps       = 24;
    player->frame     = 0;

    player->frameUpdateThread = SDL_CreateThread(frameUpdate, "frameUpdate", player);
    player->threadIsRunning   = 1;

    return player;
}

/**
 * @brief   
 * @param   player
 * @return  
 * @ingroup Player
 */
int8_t playerReloadSprite(Player *player)
{
    player->sprite = IMG_Load(player->file);

    if (NULL == player->sprite)
    {
        fprintf(stderr, "Couldn't load image: %s\n", IMG_GetError());
        return -1;
    }

    return 0;
}

/**
 * @brief 
 * @param player
 * @param config
 * @param keyState
 * @return 
 * @ingroup Player
 */
uint8_t playerUpdate(Player *player, config_t config, const uint8_t *keyState)
{
    // Reset inMotion state (in case no key is pressed).
    player->inMotion = 0;

    uint16_t keyUp    = SDL_GetScancodeFromName(configGetString(config, "controls.up"));
    uint16_t keyDown  = SDL_GetScancodeFromName(configGetString(config, "controls.down"));
    uint16_t keyLeft  = SDL_GetScancodeFromName(configGetString(config, "controls.left"));
    uint16_t keyRight = SDL_GetScancodeFromName(configGetString(config, "controls.right"));
    uint16_t keyQuit  = SDL_GetScancodeFromName(configGetString(config, "controls.quit"));

    if (keyState[keyQuit])
        return 0;

    if (keyState[keyUp])
    {
        player->direction = DIRECTION_UP;
        player->inMotion = 1;
        player->posY--;
    }

    if (keyState[keyDown])
    {
        player->direction = DIRECTION_DOWN;
        player->inMotion = 1;
        player->posY++;
    }

    if (keyState[keyLeft])
    {
        player->direction = DIRECTION_LEFT;
        player->inMotion = 1;
        player->posX--;
    }

    if (keyState[keyRight])
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
 * @ingroup Player
 */
void playerTerminate(Player *player)
{
    player->threadIsRunning = 0;
    SDL_WaitThread(player->frameUpdateThread, NULL);
    free(player);
    SDL_FreeSurface(player->sprite);
}
