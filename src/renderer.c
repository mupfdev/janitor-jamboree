/** @file renderer.c
 * @ingroup   Renderer
 * @defgroup  Renderer
 * @brief     The game's graphics renderer.
 * @author    Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 */

#include "renderer.h"

/**
 * @brief   
 * @param   screen
 * @return  
 * @ingroup Renderer
 */
Renderer *rendererInit(Screen *screen)
{
    static Renderer *renderer;
    renderer = malloc(sizeof(struct RendererType));

    renderer->renderer  = SDL_CreateRenderer(screen->window, -1, SDL_RENDERER_ACCELERATED);
    renderer->playerTex = NULL;

    if (NULL == renderer->renderer)
    {
        fprintf(stderr, "Couldn't create renderer: %s\n", SDL_GetError());
        return NULL;
    }

    return renderer;
}

/**
 * @brief 
 * @param   screen
 * @param   renderer
 * @param   player
 * @return  
 * @ingroup Renderer
 */
int8_t render(Screen *screen, Renderer *renderer, Player *player)
{
    //Render player.
    int32_t screenWidth;
    int32_t screenHeight;

    SDL_GetWindowSize(screen->window, &screenWidth, &screenHeight);
    
    int16_t playerPosX = (screenWidth / 2) - 32;
    int16_t playerPosY = (screenHeight / 2) - 32;

    if (NULL == renderer->playerTex)
        renderer->playerTex = SDL_CreateTextureFromSurface(renderer->renderer, player->sprite);

    SDL_Rect playerSrc = { player->frame * 64, player->direction, 64, 64 };
    SDL_Rect playerDst = { playerPosX, playerPosY, 64, 64 };

    if (-1 == SDL_RenderCopy(renderer->renderer, renderer->playerTex, &playerSrc, &playerDst))
    {
        fprintf(stderr, "%s\n", SDL_GetError());
        return -1;
    }

    SDL_RenderPresent(renderer->renderer);
    SDL_RenderClear(renderer->renderer);

    return 0;
}

/**
 * @brief   
 * @param   renderer
 * @ingroup Renderer
 */
void rendererTerminate(Renderer *renderer)
{
    SDL_DestroyRenderer(renderer->renderer);
}
