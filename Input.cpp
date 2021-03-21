#include "Input.h"
#include <iostream>

void Input::translateEventAndProcessCommand()
{
    SDL_PollEvent(&event);
    switch(event.type)
    {
    case SDL_KEYDOWN:
        try
        {
            if(mapArray[event.key.keysym.sym])
                mapArray[event.key.keysym.sym]->proc();

            if(event.key.keysym.sym > sizeof(mapArray))
                throw std::string("out of bounds - Input::translateEventAndProcessCommand()");
        }
        catch(std::string error)
        {
            std::cerr << error;
        }
        break;
    }
}
