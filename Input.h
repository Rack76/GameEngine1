#ifndef INPUT_H
#define INPUT_H

#include "SDL2/SDL.h"
#include "ACamera.h"
#include "Camera.h"

class Input

{
public:
    Input(ACamera* camera)
    {
        this->camera = camera;
    }
	void getInput();

private:
	SDL_Event event;
	ACamera* camera;
};

#endif
