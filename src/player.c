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
 *          long @c plr->inMotion @c is set to 1.  See @ref struct playerType.
 * @param   plr The player structure.  See @ref struct playerType.
 * @ingroup Player
 */
static void *frameUpdate(void *plr)
{
    player *playr = (player *)plr;

    while(1)
    {
        if (playr->inMotion)
        {
            usleep(1000000 / playr->fps);
            playr->frame++;
        }
        else
            playr->frame = 0;

        (9 <= playr->frame) && (playr->frame = 0);
    }

    return NULL;
}

/**
 * @brief   Initialise a player structure.  See @ref struct playerType.
 * @return  A pointer to a player structure on success, NULL on error.
 * @ingroup Player
 */
player *playerInit()
{
    static player *plr;
    plr = malloc(sizeof(struct playerType));

    // Set default values.
    plr->file   = "res/sprites/male.png";
    plr->sprite = IMG_Load(plr->file);

    if (NULL == plr->sprite)
    {
        fprintf(stderr, "Couldn't load image: %s\n", IMG_GetError());
        return NULL;
    }

    plr->direction = DIRECTION_DOWN;
    plr->inMotion  = 0;
    plr->fps       = 24;
    plr->frame     = 0;

    pthread_create(&plr->frameUpdateThread, NULL, frameUpdate, plr);

    return plr;
}

/**
 * @brief              Update the player's current state and display it's
 *                     sprite.  Usually called within the game's main loop.
 * @param plr          The player struct.  See @ref struct playerType.
 * @param config       Initialised config_t structure.
 * @param keyState     Pointer to keyState array. See @ref struct inputType.
 * @return             1 on success, 0 on quit.
 * @ingroup Player
 */
int8_t playerUpdate(player *plr, config_t config, uint8_t *keyState)
{
    // Reset inMotion state (in case no key is pressed).
    plr->inMotion = 0;

    uint16_t keyUp    = configGetInt(config, "controls.up");
    uint16_t keyDown  = configGetInt(config, "controls.down");
    uint16_t keyLeft  = configGetInt(config, "controls.left");
    uint16_t keyRight = configGetInt(config, "controls.right");
    uint16_t keyQuit  = configGetInt(config, "controls.quit");

    if ((keyState[keyQuit]) && (keyState[SDLK_LCTRL]))
        return 0;

    if (keyState[keyUp])
    {
        plr->direction = DIRECTION_UP;
        plr->inMotion = 1;
        plr->posY--;
    }

    if (keyState[keyDown])
    {
        plr->direction = DIRECTION_DOWN;
        plr->inMotion = 1;
        plr->posY++;
    }

    if (keyState[keyLeft])
    {
        plr->direction = DIRECTION_LEFT;
        plr->inMotion = 1;
        plr->posX--;
    }

    if (keyState[keyRight])
    {
        plr->direction = DIRECTION_RIGHT;
        plr->inMotion = 1;
        plr->posX++;
    }

    if (plr->posX <= 0)     plr->posX = 0;
    if (plr->posX >= 65535) plr->posX = 65535;
    if (plr->posY <= 0)     plr->posY = 0;
    if (plr->posY >= 65535) plr->posY = 65535;

    return 1;
}

/**
 * @brief   Terminate player.
 * @param   plr The player structure.  See @ref struct playerType.
 * @ingroup Player
 */
void playerTerminate(player *plr)
{
    free(plr);
    SDL_FreeSurface(plr->sprite);
    pthread_cancel(plr->frameUpdateThread);
}
