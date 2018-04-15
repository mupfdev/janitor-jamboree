/* main.c -*-c-*-
 * Janitor Jamboree
 * A constantly evolving project I work on to learn the art of game programming
 * and design patterns.
 *
 * "THE BEER-WARE LICENCE" (Revision 42):
 * See the file LICENSE.md for details */

#include "main.h"

int main(int argc, char *argv[])
{
    config_t config;
    char *configFile = NULL; 

    if (argc == 2)
        configFile = argv[1];

    config = configInit(config, configFile);

    uint16_t screenWidth = configGetInt(config, "video.width");
    uint16_t screenHeight = configGetInt(config, "video.height");
    uint8_t  screenFullscreen = configGetBool(config, "video.fullscreen");
    const char *title = "Janitor Jamboree";

    SDL_Surface *screen;
    screen = screenInit(screenWidth, screenHeight, screenFullscreen, title);
    if (NULL == screen)
        return EXIT_FAILURE;

    input *controls = inputInit();
    if (NULL == controls)
        return EXIT_FAILURE;

    player *hero = playerInit();
    if (NULL == hero)
        return EXIT_FAILURE;

    uint8_t gameIsRunning = 1;
    while(gameIsRunning)
    {
        inputGetKeys(controls);
        if (-1 == playerRender(screen, screenWidth, screenHeight, hero))
            return EXIT_FAILURE;

        hero->isWalking = 0;

        if (controls->state[SDLK_w])
        {
            hero->direction = DIRECTION_UP;
            hero->isWalking = 1;
        }
        if (controls->state[SDLK_s])
        {
            hero->direction = DIRECTION_DOWN;
            hero->isWalking = 1;
        }
        if (controls->state[SDLK_a])
        {
            hero->direction = DIRECTION_LEFT;
            hero->isWalking = 1;
        }
        if (controls->state[SDLK_d])
        {
            hero->direction = DIRECTION_RIGHT;
            hero->isWalking = 1;
        }

        if (controls->state[SDLK_q])
            gameIsRunning = 0;
    }

    atexit(quitGame);
    return EXIT_SUCCESS;
}

void quitGame()
{
    screenTerminate();
}
