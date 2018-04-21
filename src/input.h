/** @file input.h
 * @ingroup Input
 */

#ifndef INPUT_h
#define INPUT_h

#include <SDL2/SDL.h>

/**
 * @ingroup Input
 */
struct InputType {
    const uint8_t *keyState;
};

typedef struct InputType Input;

Input *inputInit();
uint8_t inputGetKeys(Input *input);
void inputTerminate(Input *input);

#endif
