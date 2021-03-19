#include "Window.h"

Window::Window(int XLocation, int YLocation, int width, int height)
{
    SDL_Init(SDL_INIT_EVERYTHING);//initialise sdl
    window = SDL_CreateWindow("window", XLocation, YLocation, width, height, SDL_WINDOW_OPENGL);//create a window
    context = SDL_GL_CreateContext(window);//create a context
}

void Window::render()
{
    SDL_GL_SwapWindow(window);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::cleanUp()
{
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
