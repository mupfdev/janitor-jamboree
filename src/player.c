/* player.c -*-c-*-
 * Everything related to the game's player entity.
 *
 * "THE BEER-WARE LICENCE" (Revision 42):
 * See the file LICENSE.md for details */

#include "player.h"

player *playerInit()
{
    static player *plr;
    plr = malloc(sizeof(struct playerType));

    // Initialise default values.
    plr->file = "res/sprites/princess.png";
    plr->sprite = IMG_Load(plr->file);

    if (NULL == plr->sprite)
    {
        fprintf(stderr, "Couldn't load image: %s\n", IMG_GetError());
        return NULL;
    }

    plr->direction = DIRECTION_DOWN;
    plr->inMotion = 0;
    plr->frame = 0;
    plr->refreshCounter = 1;
    plr->refreshRate = 100; // The higher the value, the slower the animation.

    return plr;
}

int8_t playerUpdate(
    SDL_Surface *screen,
    uint8_t *keyState, uint8_t quit,
    uint16_t screenWidth, uint16_t screenHeight,
    player *plr)
{
    int16_t xPos = (screenWidth / 2) - 32;
    int16_t yPos = (screenHeight / 2) - 32;

    // Set-up controls.
    if (quit)
        return -2;

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

    // Test code to speed up the sprite animation.
    if (keyState[SDLK_LSHIFT])
        plr->refreshRate = 30;
    else
        plr->refreshRate = 100;

    /* Slow down sprite animation,
     * reset animation if no key is pressed,
     * repeat animation. */
    (plr->inMotion) ? (plr->refreshCounter++) : (plr->frame = 0);
    plr->inMotion = 0;

    if ((plr->refreshCounter % plr->refreshRate) == 0)
        plr->frame++;

    (plr->refreshCounter > plr->refreshRate) && (plr->refreshCounter = 1);  

    (9 <= plr->frame) && (plr->frame = 0);

    // Update sprite.
    SDL_Rect src = { plr->frame * 64, plr->direction, 64, 64 };
    SDL_Rect dst = { xPos, yPos, 64, 64 };

    if (-1 == SDL_BlitSurface(plr->sprite, &src, screen, &dst))
    {
        fprintf(stderr, "%s\n", SDL_GetError());
        return -1;
    }
    SDL_UpdateRect(screen, xPos, yPos, 64, 64);

    // Temporary. Please fix me later on.
    SDL_FillRect(screen, NULL, 0x000000);

    return 0;
}

void playerTerminate(player *plr)
{
    SDL_FreeSurface(plr->sprite);
}
