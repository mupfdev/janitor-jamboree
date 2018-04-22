/** @file renderer.c
 * @ingroup   Renderer
 * @defgroup  Renderer
 * @brief     Functions to draw everything on screen.
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
static uint32_t gidClearFlags(unsigned int gid) {
    return gid & TMX_FLIP_BITS_REMOVAL;
}

/**
 * @brief   
 * @param   renderer
 * @param   map
 * @param   layers
 * @ingroup Map
 */
static void drawLayers(Renderer *renderer, tmx_map *map, tmx_layer *layers) {
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
 * @param   screen
 * @param   renderer
 * @param   player
 * @return  
 * @ingroup Renderer
 */
int8_t drawGame(Screen *screen, Renderer *renderer, Player *player, Map *map)
{
    int32_t screenWidth;
    int32_t screenHeight;

    SDL_GetWindowSize(screen->window, &screenWidth, &screenHeight);
    
    int16_t playerPosX = (screenWidth / 2) - 32;
    int16_t playerPosY = (screenHeight / 2) - 32;

    // Render map.
    SDL_Rect mapDst;
    mapDst.w = map->tmx->width  * map->tmx->tile_width;
    mapDst.h = map->tmx->height * map->tmx->tile_height;
    mapDst.x = (screenWidth  / 2) - (mapDst.w / 2) + player->mapPosX;
    mapDst.y = (screenHeight / 2) - (mapDst.h / 2) + player->mapPosY;

    if (NULL == renderer->mapRendered)
    {
        fprintf(stderr, "%s\n", SDL_GetError());
        return -1;
    }

    if (-1 == SDL_RenderCopy(renderer->renderer, renderer->mapRendered, NULL, &mapDst))
    {
        fprintf(stderr, "%s\n", SDL_GetError());
        return -1;
    }

    // Render player.
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
    SDL_Rect playerDst = { playerPosX, playerPosY, 64, 64 };

    if (-1 == SDL_RenderCopy(renderer->renderer, renderer->player, &playerSrc, &playerDst))
    {
        fprintf(stderr, "%s\n", SDL_GetError());
        return -1;
    }

    SDL_RenderPresent(renderer->renderer);
    SDL_RenderClear(renderer->renderer);

    // Set boundaries (needs cleanup).
    if (player->mapPosX > (int32_t)(mapDst.w / 2) - 16)
        player->mapPosX = (mapDst.w / 2) - 16;
    if (player->mapPosX < (int32_t)(((mapDst.w / 2) - (mapDst.w)) + 16))
        player->mapPosX = (mapDst.w / 2) - (mapDst.w) + 16;
    if (player->mapPosY > (int32_t)(mapDst.h / 2))
        player->mapPosY = (mapDst.h / 2);
    if (player->mapPosY < (int32_t)((mapDst.h / 2) - (mapDst.h) + 32))
        player->mapPosY = (mapDst.h / 2) - (mapDst.h) + 32;

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
    renderer->renderer    = SDL_CreateRenderer(screen->window, -1, SDL_RENDERER_ACCELERATED);

    if (NULL == renderer->renderer)
    {
        fprintf(stderr, "Couldn't create renderer: %s\n", SDL_GetError());
        return NULL;
    }

    return renderer;
}

/**
 * @brief   
 * @param   renderer
 * @param   map
 * @return  
 * @ingroup Map
 */
int8_t renderMap(Renderer *renderer, Map *map)
{
    if (NULL == renderer->mapTileset)
        renderer->mapTileset = IMG_LoadTexture(renderer->renderer, "res/tilesets/terrain_atlas.png");

    if (NULL == renderer->mapTileset)
    {
        fprintf(stderr, "%s\n", SDL_GetError());
        return -1;
    }

    uint32_t width  = map->tmx->width  * map->tmx->tile_width;
    uint32_t height = map->tmx->height * map->tmx->tile_height;

    renderer->mapRendered = SDL_CreateTexture(
        renderer->renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        width,
        height);

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
    drawLayers(renderer, map->tmx, map->tmx->ly_head);

    if (-1 == SDL_SetRenderTarget(renderer->renderer, NULL))
    {
        puts("3");
        fprintf(stderr, "%s\n", SDL_GetError());
        return -1;
    }

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
