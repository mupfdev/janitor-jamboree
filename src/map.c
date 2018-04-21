/** @file map.c
 * @ingroup   Map
 * @defgroup  Map
 * @brief     The map handler.
 * @author    Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 */

#include "map.h"

/**
 * @brief   
 * @return  
 * @ingroup Map
 */
Map *mapInit()
{
    static Map *map;
    map = malloc(sizeof(struct MapType));

    map->tmxMap = tmx_load("res/maps/outskirts.tmx");

    if (NULL == map->tmxMap) {
        fprintf(stderr, "%s\n", tmx_strerr());
        return NULL;
    }

    //tmx_img_load_func = (void* (*)(const char*))IMG_Load;
    //

    return map;
}

/**
 * @brief   
 * @param   map
 * @ingroup Map
 */
void mapTerminate(Map *map)
{
    tmx_map_free(map->tmxMap);
}
