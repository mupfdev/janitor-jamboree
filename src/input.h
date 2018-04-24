/** @file input.h
 * @ingroup Input
 */

#ifndef INPUT_h
#define INPUT_h

#include <SDL2/SDL.h>

/**
 * @ingroup Input
 */
typedef struct input_t {
    const uint8_t *keyState;
} Input;

Input  *inputInit();
int8_t inputLoop(Input *input);
void   inputTerminate(Input *input);

#endif
