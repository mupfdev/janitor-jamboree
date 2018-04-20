/** @file renderer.c
 * @ingroup   Render
 * @defgroup  Render
 * @brief     The game's graphics renderer.
 * @author    Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 */

#include "render.h"

int8_t render(SDL_Surface *screen, player *plr)
{
    int16_t plrPosX = (screen->w / 2) - 32;
    int16_t plrPosY = (screen->h / 2) - 32;

    SDL_Rect src = { plr->frame * 64, plr->direction, 64, 64 };
    SDL_Rect dst = { plrPosX, plrPosY, 64, 64 };

    if (-1 == SDL_BlitSurface(plr->sprite, &src, screen, &dst))
    {
        fprintf(stderr, "%s\n", SDL_GetError());
        return -1;
    }

    SDL_UpdateRect(screen, plrPosX, plrPosY, 64, 64);

    // Fill screen black. Temporary fix until the map is implemented.
    SDL_FillRect(screen, NULL, 0x000000);

    return 0;
}
