#include "Input.h"

void Input::translateEventAndProcessCommand()
{
    SDL_PollEvent(&event);
    switch(event.type)
    {
    case SDL_KEYDOWN:
        mapArray[event.key.keysym.sym]->proc();
        break;
    }
}
