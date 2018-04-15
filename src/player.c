/* player.c -*-c-*-
 * Everything related to the game's player entity.
 *
 * "THE BEER-WARE LICENCE" (Revision 42):
 * See the file LICENSE.md for details */

#include "player.h"

player *playerInit()
{
    static player *plr;
    plr = malloc(sizeof(struct playerData));

    // Initialise default values.
    plr->file = "res/sprites/male_walkcycle.png";
    plr->sprite = IMG_Load(plr->file);

    if (NULL == plr->sprite)
    {
        fprintf(stderr, "Couldn't load image: %s\n", IMG_GetError());
        return NULL;
    }

    plr->direction = DIRECTION_DOWN;
    plr->isWalking = 0;
    plr->frame = 0;

    return plr;
}

int8_t playerRender(
    SDL_Surface *screen,
    uint16_t screenWidth, uint16_t screenHeight,
    player *plr)
{
    int16_t xPos = (screenWidth / 2) - 32;
    int16_t yPos = (screenHeight / 2) - 32;

    (plr->isWalking) ? (plr->frame++) : (plr->frame = 0);
    if (9 <= plr->frame)
        plr->frame = 0;

    SDL_Rect src = { plr->frame * 64, plr->direction, 64, 64 };
    SDL_Rect dst = { xPos, yPos, 64, 64 };

    if (-1 == SDL_BlitSurface(plr->sprite, &src, screen, &dst))
    {
        fprintf(stderr, "%s\n", SDL_GetError());
        return -1;
    }
    SDL_UpdateRect(screen, xPos, yPos, 64, 64);
    if (plr->isWalking)
        SDL_Delay(50);

    // Temporary. Please fix me later on.
    SDL_FillRect(screen, NULL, 0x000000);

    return 0;
}
