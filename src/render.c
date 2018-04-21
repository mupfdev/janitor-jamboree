/** @file renderer.c
 * @ingroup   Render
 * @defgroup  Render
 * @brief     The game's graphics renderer.
 * @author    Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 */

#include "render.h"

int8_t render(SDL_Surface *screen, Player *player)
{
    int16_t playerPosX = (screen->w / 2) - 32;
    int16_t playerPosY = (screen->h / 2) - 32;

    SDL_Rect src = { player->frame * 64, player->direction, 64, 64 };
    SDL_Rect dst = { playerPosX, playerPosY, 64, 64 };

    if (-1 == SDL_BlitSurface(player->sprite, &src, screen, &dst))
    {
        fprintf(stderr, "%s\n", SDL_GetError());
        return -1;
    }

    SDL_UpdateRect(screen, playerPosX, playerPosY, 64, 64);

    // Fill screen black. Temporary fix until the map is implemented.
    SDL_FillRect(screen, NULL, 0x000000);

    return 0;
}
