/** @file map.c
 * @ingroup   Map
 * @defgroup  Map
 * @brief     Functions to load and process tmx map files.
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
    map = malloc(sizeof(struct map_t));

    map->gidCenter = 0;
    map->tmx = NULL;

    return map;
}

/**
 * @brief   
 * @param   map
 * @return  
 * @ingroup Map
 */
int8_t mapLoadTmx(Map *map)
{
    map->tmx = tmx_load(map->filename);

    if (NULL == map->tmx) {
        fprintf(stderr, "%s\n", tmx_strerr());
        return -1;
    }

    return 0;
}

/**
 * @brief   
 * @param   map
 * @ingroup Map
 */
void mapTerminate(Map *map)
{
    tmx_map_free(map->tmx);
    free(map);
}
