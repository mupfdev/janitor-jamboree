/* player.c -*-c-*-
 * Everything related to the game's player entity.
 *
 * "THE BEER-WARE LICENCE" (Revision 42):
 * See the file LICENSE.md for details */

#include "player.h"

struct player *playerInit()
{
    static struct player *player;
    player = malloc(sizeof(struct player));

    // Initialise default values.
    player->file = "res/sprites/princess.png";
    player->sprite = IMG_Load(player->file);

    if (NULL == player->sprite)
        fprintf(stderr, "Couldn't load image: %s\n", IMG_GetError());

    player->direction = DOWN;

    return player;
}

int8_t playerRender(
    SDL_Surface *screen,
    uint16_t screenWidth, uint16_t screenHeight,
    struct player *player)
{
    int32_t xPos = (screenWidth / 2) - 32;
    int32_t yPos = (screenHeight / 2) - 32;

    SDL_BlitSurface(player->sprite, NULL, screen, NULL);
    SDL_UpdateRect(screen, 0, 0, 0, 0);

    // Temporarily suppress error due unused variables.
    int suppressWarning = xPos + yPos;
    if (suppressWarning != 0) suppressWarning = 0;

    return 0;
}
