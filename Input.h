#ifndef INPUT_H
#define INPUT_H

#include "SDL2/SDL.h"
#include "ACamera.h"
#include "DataBus.h"
#include "Command.h"

class Input
{
public:
    Input(DataBus* dtBus)
    {
        this->dtBus = dtBus;
        mapArray = new Command*[2000];
        for(int i = 0; i < 2000; i++)
            mapArray[i] = nullptr;
    }
	void translateEventAndProcessCommand();
    void insertCommand(int SDL_EVENT, Command* cmd);


    DataBus* dtBus;
	SDL_Event event;
    Command **mapArray;
};

#endif
