/** @file main.c
 * @author    Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 * @todo      Add configuration handler.
 */

#include "main.h"

/**
 * @brief  Main program.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on error
 */
int main()
{
    // Initialisation.
    Screen *screen;
    screen = screenInit();
    if (NULL == screen) return EXIT_FAILURE;

    atexit(SDL_Quit);

    Renderer *renderer;
    renderer = rendererInit(screen);
    if (NULL == renderer) return EXIT_FAILURE;

    Input *input = inputInit();
    if (NULL == input) return EXIT_FAILURE;

    Player *player = playerInit();
    if (NULL == player) return EXIT_FAILURE;

    Map *map = mapInit();
    if (NULL == map) return EXIT_FAILURE;

    /* Note: The error handling isn't missing.  There is simply no need to quit
     * the program if the music can't be played by some reason. */
    Mixer *mixer = mixerInit();
    Music *music = musicInit();
    musicFadeIn(music, 5000);

    // Main loop.  
    uint8_t gameIsRunning = 1;
    while(gameIsRunning)
    {
        gameIsRunning = inputLoop(input);
        if (1 == gameIsRunning)
        {
            gameIsRunning = playerLoop(player, input->keyState);
            render(screen, renderer, player);
        }
    }

    // Cleanup.
    musicTerminate(music);
    mixerTerminate(mixer);
    mapTerminate(map);
    playerTerminate(player);
    inputTerminate(input);
    rendererTerminate(renderer);
    screenTerminate(screen);

    return EXIT_SUCCESS;
}
