/* music.c -*-c-*-
 * In-game music handler.
 *
 * "THE BEER-WARE LICENCE" (Revision 42):
 * See the file LICENSE.md for details */

#include "music.h"

music *initMusic()
{
    static music *tune;
    tune = malloc(sizeof(struct musicType));

    return tune;
}
