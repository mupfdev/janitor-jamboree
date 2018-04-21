/** @file renderer.h
 * @ingroup   Renderer
 * @defgroup  Renderer
 * @brief     The game's graphics renderer.
 * @author    Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 */

#ifndef RENDERER_h
#define RENDERER_h

#include "player.h"
#include "screen.h"

/**
 * @ingroup Renderer
 */
struct RendererType {
    SDL_Texture  *playerTex;
    SDL_Renderer *renderer;
};

typedef struct RendererType Renderer;

Renderer *rendererInit(Screen *screen);
int8_t render(Screen *screen, Renderer *renderer, Player *player);
void rendererTerminate(Renderer *renderer);

#endif
