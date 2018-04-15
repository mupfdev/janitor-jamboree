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
    config_t config = configInit(config, NULL);
    uint16_t screenWidth = configGetInt(config, "video.width");
    uint16_t screenHeight = configGetInt(config, "video.height");
    uint8_t  screenFullscreen = configGetBool(config, "video.fullscreen");
    const char *title = "Janitor Jamboree";

    SDL_Surface *screen;
    screen = screenInit(screenWidth, screenHeight, screenFullscreen, title);
    if (NULL == screen)
        return EXIT_FAILURE;

    if (-1 == inputInit())
        return EXIT_FAILURE;

    player *hero = playerInit();
    uint8_t gameIsRunning = 1;

    while(gameIsRunning)
    {
        playerRender(screen, screenWidth, screenHeight, hero);
        uint32_t event = inputPollEvent();

        switch(event)
        {
            case KEYUP:
                hero->frame = 0;
                break;
            case SDLK_UP:
            case SDLK_w:
                hero->direction = UP;
                hero->frame++;
                break;
            case SDLK_DOWN:
            case SDLK_s:
                hero->direction = DOWN;
                hero->frame++;
                break;
            case SDLK_LEFT:
            case SDLK_a:
                hero->direction = LEFT;
                hero->frame++;
                break;
            case SDLK_RIGHT:
            case SDLK_d:
                hero->direction = RIGHT;
                hero->frame++;
                break;
            case SDL_QUIT:
            case SDLK_ESCAPE:
            case SDLK_q:
                gameIsRunning = 0;
                break;
        }
    }

    atexit(quitGame);
    return EXIT_SUCCESS;
}

void quitGame()
{
    screenTerminate();
}
