/** @file renderer.h
 * @ingroup Renderer
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
typedef struct renderer_t {
    SDL_Texture  *mapTileset;
    SDL_Texture  *mapRenderedOverlay;
    SDL_Texture  *mapRenderedTerrain;
    SDL_Texture  *player;
    SDL_Renderer *renderer;
} Renderer;

Renderer *rendererInit(Screen *screen);
int8_t   renderScene(Screen *screen, Renderer *renderer, Player *player, Map *map);
void     rendererTerminate(Renderer *renderer);

#endif
