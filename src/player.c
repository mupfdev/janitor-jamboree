/* player.c -*-c-*-
 * Everything related to the game's player entity.
 *
 * "THE BEER-WARE LICENCE" (Revision 42):
 * See the file LICENSE.md for details */

#include "player.h"

player *playerInit()
{
    static player *player;
    player = malloc(sizeof(struct playerInfo));

    // Initialise default values.
    player->file = "res/sprites/soldier_altcolor.png";
    player->sprite = IMG_Load(player->file);

    if (NULL == player->sprite)
        fprintf(stderr, "Couldn't load image: %s\n", IMG_GetError());

    player->direction = DOWN;

    return player;
}

int8_t playerRender(
    SDL_Surface *screen,
    uint16_t screenWidth, uint16_t screenHeight,
    player *player)
{
    int16_t xPos = (screenWidth / 2) - 32;
    int16_t yPos = (screenHeight / 2) - 32;

    if (player->frame >= 9)
        player->frame = 0;

    SDL_Rect src = { player->frame * 64, player->direction, 64, 64 };
    SDL_Rect dst = { xPos, yPos, 64, 64 };

    SDL_BlitSurface(player->sprite, &src, screen, &dst);
    SDL_UpdateRect(screen, xPos, yPos, 64, 64);

    // Temporary. Please fix me later on.
    SDL_FillRect(screen, NULL, 0x000000);

    return 0;
}
