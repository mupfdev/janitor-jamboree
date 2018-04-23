/** @file renderer.c
 * @ingroup   Renderer
 * @defgroup  Renderer
 * @brief     The graphics renderer.
 * @author    Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 */

#include "renderer.h"

/**
 * @brief   
 * @param   gid
 * @return  
 * @ingroup Map
 */
static uint32_t gidClearFlags(unsigned int gid)
{
    return gid & TMX_FLIP_BITS_REMOVAL;
}

/**
 * @brief   
 * @param   renderer
 * @param   map
 * @param   layers
 * @ingroup Map
 */
static void renderLayers(Renderer *renderer, tmx_map *map, tmx_layer *layers) {
    SDL_Rect    src;
    SDL_Rect    dst;
    uint32_t    gid;
    uint32_t    ih;
    uint32_t    iw;
    tmx_tileset *ts;

    while (layers)
    {
        if (layers->visible)
        {
            for (ih = 0; ih < map->height; ih++)
                for (iw = 0; iw < map->width; iw++)
                {
                    gid = gidClearFlags(layers->content.gids[(ih * map->width) + iw]);
                    if (map->tiles[gid] != NULL)
                    {
                        ts    = map->tiles[gid]->tileset;
                        src.x = map->tiles[gid]->ul_x;
                        src.y = map->tiles[gid]->ul_y;
                        src.w = dst.w = ts->tile_width;
                        src.h = dst.h = ts->tile_height;
                        dst.x = iw * ts->tile_width;
                        dst.y = ih * ts->tile_height;

                        SDL_RenderCopy(
                            renderer->renderer,
                            renderer->mapTileset,
                            &src,
                            &dst);
                    }
                }
        }
        layers = layers->next;
    }
}

/**
 * @brief    
 * @param   renderer
 * @param   map
 * @param   posX
 * @param   posY
 * @ingroup Renderer
 * @return  
 */
static int8_t renderMap(Renderer *renderer, Map *map, int16_t posX, int16_t posY)
{
    if (NULL == renderer->mapTileset)
        renderer->mapTileset = IMG_LoadTexture(renderer->renderer, "res/tilesets/terrain_atlas.png");

    if (NULL == renderer->mapTileset)
    {
        fprintf(stderr, "%s\n", SDL_GetError());
        return -1;
    }

    SDL_Rect mapDst;
    mapDst.w = map->tmx->width  * map->tmx->tile_width;
    mapDst.h = map->tmx->height * map->tmx->tile_height;
    mapDst.x = posX;
    mapDst.y = posY;

    if (NULL == renderer->mapRendered)
        renderer->mapRendered = SDL_CreateTexture(
            renderer->renderer,
            SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_TARGET,
            mapDst.w,
            mapDst.h);

    if (NULL == renderer->mapRendered)
    {
        fprintf(stderr, "%s\n", SDL_GetError());
        return -1;
    }

    if (-1 == SDL_SetRenderTarget(renderer->renderer, renderer->mapRendered))
    {
        fprintf(stderr, "%s\n", SDL_GetError());
        return -1;
    }

    SDL_SetRenderDrawColor(renderer->renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer->renderer);

    renderLayers(renderer, map->tmx, map->tmx->ly_head);

    if (-1 == SDL_SetRenderTarget(renderer->renderer, NULL))
    {
        puts("3");
        fprintf(stderr, "%s\n", SDL_GetError());
        return -1;
    }

    if (-1 == SDL_RenderCopy(renderer->renderer, renderer->mapRendered, NULL, &mapDst))
    {
        fprintf(stderr, "%s\n", SDL_GetError());
        return -1;
    }

    return 0;
}

/**
 * @brief   
 * @param   renderer
 * @param   player
 * @param   posX
 * @param   posY
 * @return  
 * @ingroup Renderer
 */
static int8_t renderPlayer(Renderer *renderer, Player *player, int16_t posX, int16_t posY)
{
    if (0 == ((player->flags >> SPRITE_LOCK) & 1))
    {
        SDL_DestroyTexture(renderer->player);
        renderer->player = IMG_LoadTexture(renderer->renderer, player->filename);
        player->flags |= 1 << SPRITE_LOCK;
    }

    if (NULL == renderer->player)
    {
        fprintf(stderr, "%s\n", SDL_GetError());
        return -1;
    }

    SDL_Rect playerSrc = { player->frame * 64, player->direction, 64, 64 };
    SDL_Rect playerDst = { posX, posY, 64, 64 };

    if (-1 == SDL_RenderCopy(renderer->renderer, renderer->player, &playerSrc, &playerDst))
    {
        fprintf(stderr, "%s\n", SDL_GetError());
        return -1;
    }

    return 0;
}

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

    renderer->mapRendered = NULL;
    renderer->mapTileset  = NULL;
    renderer->player      = NULL;

    renderer->renderer = SDL_CreateRenderer(
        screen->window,
        -1,
        SDL_RENDERER_ACCELERATED);

    if (NULL == renderer->renderer)
    {
        fprintf(stderr, "Couldn't create renderer: %s\n", SDL_GetError());
        free(renderer);
        return NULL;
    }

    return renderer;
}

/**
 * @brief   
 * @param   screen
 * @param   renderer
 * @param   player
 * @param   map
 * @return  
 * @ingroup Renderer
 */
int8_t renderScene(Screen *screen, Renderer *renderer, Player *player, Map *map)
{
    int32_t screenWidth;
    int32_t screenHeight;

    SDL_GetWindowSize(screen->window, &screenWidth, &screenHeight);

    player->renderPosX = (screenWidth / 2)  - 32;
    player->renderPosY = (screenHeight / 2) - 32;

    player->mapPosX = (screenWidth  / 2) - (screenWidth  / 2) + player->mapPosX;
    player->mapPosY = (screenHeight / 2) - (screenHeight / 2) + player->mapPosY;

    if (-1 == renderMap(renderer, map, player->mapPosX, player->mapPosY))
        return -1;

    if (-1 == renderPlayer(renderer, player, player->renderPosX, player->renderPosY))
        return -1;

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
    free(renderer);
}
