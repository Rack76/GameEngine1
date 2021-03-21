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
                mapArray[event.key.keysym.sym]->proc(dtBus);

            if(event.key.keysym.sym > sizeof(mapArray))
                throw std::string("out of bounds - Input::translateEventAndProcessCommand()");
        }
        catch(std::string error)
        {
            std::cerr << error;
        }
        break;
    }

    switch(event.motion.type)
    {
    case SDL_MOUSEMOTION:
        try
        {
            if(mapArray[SDL_MOUSEMOTION])
                mapArray[SDL_MOUSEMOTION]->proc(dtBus);

            if(SDL_MOUSEMOTION > sizeof(mapArray))
                throw std::string("out of bounds - Input::translateEventAndProcessCommand()");
        }
        catch(std::string error)
        {
            std::cerr << error;
        }
        break;
    }
}

void Input::insertCommand(int SDL_EVENT, Command* cmd)
{
    mapArray[SDL_EVENT] = cmd;
}
