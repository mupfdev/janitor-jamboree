/** @file input.h
 * @ingroup Input
 */

#ifndef INPUT_h
#define INPUT_h

#include <stdlib.h>
#include <SDL/SDL.h>

/**
 * @ingroup Audio
 */
struct inputType {
    uint8_t *keyState;
    uint8_t quit;
};

typedef struct inputType input;

input *inputInit();
void inputGetKeys(input *controls);

#endif
