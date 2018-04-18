/** @file player.c
 * @ingroup   Player
 * @defgroup  Player
 * @brief     Everything related to the game's player entity
 * @author    Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 */

#include "player.h"

/**
 * @brief 
 * @param plr
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
 * @brief 
 * @return 
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
 * @brief 
 * @param screen
 * @param keyState
 * @param quit
 * @param screenWidth
 * @param screenHeight
 * @param plr
 * @return 
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
 * @brief 
 * @param plr
 * @ingroup Player
 */
void playerTerminate(player *plr)
{
    free(plr);
    SDL_FreeSurface(plr->sprite);
    pthread_cancel(plr->frameUpdateThread);
}
