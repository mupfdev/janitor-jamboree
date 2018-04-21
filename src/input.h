/** @file input.h
 * @ingroup Input
 */

#ifndef INPUT_h
#define INPUT_h

#include <stdlib.h>
#include <SDL/SDL.h>

/**
 * @ingroup Input
 */
struct inputType {
    uint8_t *keyState;
};

typedef struct inputType Input;

Input *inputInit();
int8_t inputGetKeys(Input *input);
void inputTerminate(Input *input);

#endif
