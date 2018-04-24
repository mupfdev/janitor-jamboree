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
 * @param   name
 * @ingroup Map
 */
static void renderLayers(Renderer *renderer, tmx_map *map, tmx_layer *layers, const char *name) {
    SDL_Rect    src;
    SDL_Rect    dst;
    uint32_t    gid;
    uint32_t    ih;
    uint32_t    iw;
    tmx_tileset *ts;

    while (layers)
    {
        if ((layers->visible) && (NULL != strstr(layers->name, name)))
        {
            for (ih = 0; ih < map->height; ih++)
                for (iw = 0; iw < map->width; iw++)
                {
                    gid = gidClearFlags(layers->content.gids[(ih * map->width) + iw]);
                    if (NULL != map->tiles[gid])
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
 * @param   name
 * @param   posX
 * @param   posY
 * @ingroup Renderer
 * @return  
 */
static SDL_Texture *renderMap(Renderer *renderer, Map *map, const char *name)
{
    static SDL_Texture *mapRendered;
    mapRendered = NULL;

    if (NULL == renderer->mapTileset)
        renderer->mapTileset = IMG_LoadTexture(renderer->renderer, "res/tilesets/terrain_atlas.png");

    if (NULL == renderer->mapTileset)
    {
        fprintf(stderr, "%s\n", SDL_GetError());
        return NULL;
    }

    if (NULL == mapRendered)
        mapRendered = SDL_CreateTexture(
            renderer->renderer,
            SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_TARGET,
            map->tmx->width  * map->tmx->tile_width,
            map->tmx->height * map->tmx->tile_height);

    if (NULL == mapRendered)
    {
        fprintf(stderr, "%s\n", SDL_GetError());
        return NULL;
    }

    if (-1 == SDL_SetRenderTarget(renderer->renderer, mapRendered))
    {
        fprintf(stderr, "%s\n", SDL_GetError());
        return NULL;
    }

    renderLayers(renderer, map->tmx, map->tmx->ly_head, name);

    if (-1 == SDL_SetRenderTarget(renderer->renderer, NULL))
    {
        fprintf(stderr, "%s\n", SDL_GetError());
        return NULL;
    }

    return mapRendered;
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
    renderer = malloc(sizeof(struct renderer_t));

    renderer->mapRenderedOverlay = NULL;
    renderer->mapRenderedTerrain = NULL;
    renderer->mapTileset         = NULL;
    renderer->player             = NULL;

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
    SDL_Rect sceneDst;
    sceneDst.w = map->tmx->width  * map->tmx->tile_width;
    sceneDst.h = map->tmx->height * map->tmx->tile_height;

    int32_t screenWidth;
    int32_t screenHeight;

    SDL_GetWindowSize(screen->window, &screenWidth, &screenHeight);

    player->mapPosX = (screenWidth  / 2) - (screenWidth  / 2) + player->mapPosX;
    player->mapPosY = (screenHeight / 2) - (screenHeight / 2) + player->mapPosY;

    sceneDst.x = player->mapPosX;
    sceneDst.y = player->mapPosY;

    if (-1 == SDL_SetRenderDrawBlendMode(renderer->renderer, SDL_BLENDMODE_BLEND))
    {
        fprintf(stderr, "%s\n", SDL_GetError());
        return -1;
    }

    // Map boundaries.
    if (player->mapPosX >= (screenWidth / 2) - 16)
        player->mapPosX  = (screenWidth / 2) - 16;

    if (player->mapPosX <= (sceneDst.w - (sceneDst.w * 2)) + (screenWidth / 2) + 16)
        player->mapPosX  = (sceneDst.w - (sceneDst.w * 2)) + (screenWidth / 2) + 16;

    if (player->mapPosY >= (screenHeight / 2) - 16)
        player->mapPosY  = (screenHeight / 2) - 16;

    if (player->mapPosY <= (sceneDst.h - (sceneDst.w * 2)) + (screenHeight / 2) + 32)
        player->mapPosY  = (sceneDst.h - (sceneDst.w * 2)) + (screenHeight / 2) + 32;

    // Debug.
    player->posX = player->mapPosX - (screenWidth / 2);
    player->posX = abs(player->posX) / 32;

    player->posY = player->mapPosY - (screenHeight / 2);
    player->posY = abs(player->posY) / 32;

    player->test1 = (map->tmx->width * player->posY) + player->posX;
    if (player->test1 != player->test2)
        printf("%d\n", player->test1);
    player->test2 = player->test1;

    // Terrain.
    if (NULL == renderer->mapRenderedTerrain)
        renderer->mapRenderedTerrain = renderMap(renderer, map, "Terrain");
    SDL_SetTextureBlendMode(renderer->mapRenderedTerrain, SDL_BLENDMODE_BLEND);

    if (-1 == SDL_RenderCopy(renderer->renderer, renderer->mapRenderedTerrain, NULL, &sceneDst))
    {
        fprintf(stderr, "%s\n", SDL_GetError());
        return -1;
    }

    // Player;
    if (-1 == renderPlayer(renderer, player, (screenWidth  / 2) - 32, (screenHeight / 2) - 32))
        return -1;

    // Overlay.
    if (NULL == renderer->mapRenderedOverlay)
        renderer->mapRenderedOverlay = renderMap(renderer, map, "Overlay");
    SDL_SetTextureBlendMode(renderer->mapRenderedOverlay, SDL_BLENDMODE_BLEND);

    if (-1 == SDL_RenderCopy(renderer->renderer, renderer->mapRenderedOverlay, NULL, &sceneDst))
    {
        fprintf(stderr, "%s\n", SDL_GetError());
        return -1;
    }

    // Render scene.
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
