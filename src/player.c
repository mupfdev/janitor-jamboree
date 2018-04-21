/** @file player.c
 * @ingroup   Player
 * @defgroup  Player
 * @brief     Everything related to the game's hero.
 * @author    Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 */

#include "player.h"

/**
 * @brief   Function called in a separate thread to update the sprite frame as
 *          long @c player->inMotion @c is set to 1.
 *          See @ref struct playerType.
 * @param   player The Player structure.  See @ref struct playerType.
 * @return  Always 0 because a return value is expected by SDL_CreateThread().
 * @ingroup Player
 */
static int32_t frameUpdate(void *plr)
{
    Player *player = (Player *)plr;

    while(1)
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
 * @brief   Initialise a Player structure.  See @ref struct playerType.
 * @return  A pointer to a Player structure on success, NULL on error.
 * @ingroup Player
 */
Player *playerInit()
{
    static Player *player;
    player = malloc(sizeof(struct playerType));

    // Set default values.
    player->file   = "res/sprites/male.png";
    player->sprite = IMG_Load(player->file);

    if (NULL == player->sprite)
    {
        fprintf(stderr, "Couldn't load image: %s\n", IMG_GetError());
        return NULL;
    }

    player->direction = DIRECTION_DOWN;
    player->inMotion  = 0;
    player->fps       = 24;
    player->frame     = 0;

    player->frameUpdateThread = SDL_CreateThread(frameUpdate, player);

    return player;
}

/**
 * @brief              Update the player's current state and display it's
 *                     sprite.  Usually called within the game's main loop.
 * @param player       The Player structure.  See @ref struct playerType.
 * @param config       Initialised config_t structure.
 * @param keyState     Pointer to keyState array. See @ref struct inputType.
 * @return             1 on success, 0 on quit.
 * @ingroup Player
 */
int8_t playerUpdate(Player *player, config_t config, uint8_t *keyState)
{
    // Reset inMotion state (in case no key is pressed).
    player->inMotion = 0;

    uint16_t keyUp    = configGetInt(config, "controls.up");
    uint16_t keyDown  = configGetInt(config, "controls.down");
    uint16_t keyLeft  = configGetInt(config, "controls.left");
    uint16_t keyRight = configGetInt(config, "controls.right");
    uint16_t keyQuit  = configGetInt(config, "controls.quit");

    if ((keyState[keyQuit]) && (keyState[SDLK_LCTRL]))
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
 * @brief   Terminate player.
 * @param   plr The player structure.  See @ref struct playerType.
 * @ingroup Player
 */
void playerTerminate(Player *player)
{
    free(player);
    SDL_FreeSurface(player->sprite);
    SDL_KillThread(player->frameUpdateThread);
}
