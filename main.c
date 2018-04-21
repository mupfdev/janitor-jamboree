/** @file main.c
 * @author    Michael Fitzmayer
 * @copyright "THE BEER-WARE LICENCE" (Revision 42)
 */

#include "main.h"

/**
 * @brief  Main program.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on error
 */
int main()
{
    // Initialisation.
    config_t config;
    config = configInit(config, NULL);

    uint16_t   width      = configGetInt(config,    "video.width");
    uint16_t   height     = configGetInt(config,    "video.height");
    uint8_t    fullscreen = configGetBool(config,   "video.fullscreen");
    const char *title     = configGetString(config, "game.title");

    Screen *screen;
    screen = screenInit(width, height, fullscreen, title);
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

    // Main loop.  
    uint8_t gameIsRunning = 1;
    while(gameIsRunning)
    {
        gameIsRunning = inputGetKeys(input);
        if (1 == gameIsRunning)
        {
            gameIsRunning = playerUpdate(player, config, input->keyState);
            render(screen, renderer, player);
        }
    }

    mapTerminate(map);
    playerTerminate(player);
    inputTerminate(input);
    rendererTerminate(renderer);
    screenTerminate(screen);
    configTerminate(config);

    return EXIT_SUCCESS;
}
