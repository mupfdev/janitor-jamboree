/** @file map.c
 * @ingroup   Map
 * @defgroup  Map
 * @brief     Game map handler
 * @author    Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 */

#include "map.h"

/**
 * @brief 
 * @return 
 */
map *mapInit()
{
    static map *world;
    world = malloc(sizeof(struct mapType));

    return world;
}

/**
 * @brief 
 * @param world
 */
void mapTerminate(map *world)
{
    free(world);
}