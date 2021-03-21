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
        mapArray = new Command*[3000];
        for(int i = 0; i < sizeof(mapArray); i++)
            mapArray[i] = nullptr;
    }
	void translateEventAndProcessCommand();
    void insertCommand(int SDL_EVENT, Command* cmd);

private:
    DataBus* dtBus;
	SDL_Event event;
    Command **mapArray;
};

#endif
