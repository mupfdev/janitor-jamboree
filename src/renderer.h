/** @file renderer.h
 * @ingroup   Renderer
 * @defgroup  Renderer
 * @brief     The graphics renderer.
 * @author    Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 */

#ifndef RENDERER_h
#define RENDERER_h

#include <SDL2/SDL_image.h>
#include "map.h"
#include "player.h"
#include "screen.h"

/**
 * @ingroup Renderer
 */
struct RendererType {
    SDL_Texture  *mapTileset;
    SDL_Texture  *mapRendered;
    SDL_Texture  *player;
    SDL_Renderer *renderer;
};

typedef struct RendererType Renderer;

int8_t   drawGame(Screen *screen, Renderer *renderer, Player *player, Map *map);
Renderer *rendererInit(Screen *screen);
int8_t   renderMap(Renderer *renderer, Map *map);
void     rendererTerminate(Renderer *renderer);

#endif
