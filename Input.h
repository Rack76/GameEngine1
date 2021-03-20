#ifndef INPUT_H
#define INPUT_H

#include "SDL2/SDL.h"
#include "ACamera.h"
#include "DataBus.h"
#include "Command.h"

class Input
{
public:
    Input(Command **mapArray, DataBus* dtBus)
    {
        this->dtBus = dtBus;
        this->mapArray = mapArray;
    }
	void translateEventAndProcessCommand();

private:
    DataBus* dtBus;
	SDL_Event event;
    Command **mapArray;
};

#endif
