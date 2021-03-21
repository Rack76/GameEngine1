#ifndef WINDOW_H
#define WINDOW_H

#include "GL/glew.h"
#include "SDL2/SDL.h"

class Window
{
    public:
    Window(int XLocation, int YLocation, int width, int height);
    void render();
    void cleanUp();

    private:
    SDL_Window* window;
    SDL_GLContext context;
};

#endif // WINDOW_H
