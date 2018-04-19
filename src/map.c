/** @file map.c
 * @ingroup   Map
 * @defgroup  Map
 * @brief     Game map handler
 * @author    Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 */

#include "map.h"

/**
 * @brief  Initialise map.
 * @return Initialised map on success, NULL on error.
 *         See @ref struct mapType.
 */
map *mapInit()
{
    static map *world;
    world = malloc(sizeof(struct mapType));

    return world;
}

/**
 * @brief Terminate map.
 * @param world The map structure.  See @ref struct mapType.
 */
void mapTerminate(map *world)
{
    free(world);
}
