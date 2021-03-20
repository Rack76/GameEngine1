#ifndef INPUT_H
#define INPUT_H

#include "SDL2/SDL.h"

class Input

{
public:
	void getInput();
	
private:
	SDL_Event event;
};

#endif