/* main.c -*-c-*-
 * Janitor Jamboree
 * A constantly evolving project I work on to learn the art of game programming
 * and design patterns.
 *
 * "THE BEER-WARE LICENCE" (Revision 42):
 * See the file LICENSE.md for details */

#include "main.h"

int main()
{
    // Initialise configuration file.
    config_t config;
    config = configInit(config, NULL);

    // Initialise window.
    uint16_t screenWidth = configGetInt(config, "video.width");
    uint16_t screenHeight = configGetInt(config, "video.height");
    uint8_t  screenFullscreen = configGetBool(config, "video.fullscreen");
    const char *title = configGetString(config, "general.title");

    SDL_Surface *screen;
    screen = screenInit(screenWidth, screenHeight, screenFullscreen, title);
    if (NULL == screen)
        return EXIT_FAILURE;

    // Initialise input handler.
    input *controls = inputInit();
    if (NULL == controls)
        return EXIT_FAILURE;

    // Initialise player entity.
    player *hero = playerInit(config);
    if (NULL == hero)
        return EXIT_FAILURE;

    // Main game loop.
    uint8_t gameIsRunning = 1;
    puts("LCTRL+q to quit.");

    while(gameIsRunning)
    {
        inputGetKeys(controls);
        switch(playerUpdate(screen, controls->keyState, controls->quit, screenWidth, screenHeight, hero))
        {
            case -1:
                return EXIT_FAILURE;
            case -2:
                gameIsRunning = 0;
        }
    }

    // Cleanup.
    playerTerminate(hero);
    screenTerminate();
    configTerminate(config);

    return EXIT_SUCCESS;
}
