/* input.h -*-c-*-
 * Input handler.
 *
 * "THE BEER-WARE LICENCE" (Revision 42):
 * See the file LICENSE.md for details */

#ifndef INPUT_h
#define INPUT_h

#include <stdlib.h>
#include <SDL/SDL.h>

#define KEYUP 0x4000011A // SDLK_SLEEP

int8_t inputInit();
uint32_t inputPollEvent();

#endif
