/** @file player.c
 * @ingroup   Player
 * @defgroup  Player
 * @brief     Everything related to the game's player entity
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
 * @param screen       The SDL_Surface to use.
 * @param keyState     pointer to keyState array.  See @ref struct inputType.
 * @param quit         Boolean value to determine the program's quit state.
 *                     See @ref struct inputType
 * @param screenWidth  Total number of pixels along the screen's width.
 *                     Used to align the player sprite at the screen's center.
 * @param screenHeight Total number of pixels along the screen's height
 *                     Used to align the player sprite at the screen's center.
 * @param plr          The player struct.  See @ref struct playerType.
 * @return             0 on success, -1 on error, -2 on quit.
 * @ingroup Player
 */
int8_t playerUpdate(
    SDL_Surface *screen,
    uint8_t  *keyState,
    uint8_t  quit,
    uint16_t screenWidth,
    uint16_t screenHeight,
    player   *plr)
{
    int16_t xPos = (screenWidth / 2) - 32;
    int16_t yPos = (screenHeight / 2) - 32;

    // Set-up controls.
    if (quit) return -2;

    if ((keyState[SDLK_q]) && (keyState[SDLK_LCTRL]))
        return -2;

    if (keyState[SDLK_w])
    {
        plr->direction = DIRECTION_UP;
        plr->inMotion = 1;
    }

    if (keyState[SDLK_s])
    {
        plr->direction = DIRECTION_DOWN;
        plr->inMotion = 1;
    }

    if (keyState[SDLK_a])
    {
        plr->direction = DIRECTION_LEFT;
        plr->inMotion = 1;
    }

    if (keyState[SDLK_d])
    {
        plr->direction = DIRECTION_RIGHT;
        plr->inMotion = 1;
    }

    // Display updated sprite.
    SDL_Rect src = { plr->frame * 64, plr->direction, 64, 64 };
    SDL_Rect dst = { xPos, yPos, 64, 64 };

    if (-1 == SDL_BlitSurface(plr->sprite, &src, screen, &dst))
    {
        fprintf(stderr, "%s\n", SDL_GetError());
        return -1;
    }
    SDL_UpdateRect(screen, xPos, yPos, 64, 64);

    // Fill screen black. Temporary fix until the map is implemented.
    SDL_FillRect(screen, NULL, 0x000000);

    // Reset inMotion state (in case no key is pressed).
    plr->inMotion = 0;

    return 0;
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
