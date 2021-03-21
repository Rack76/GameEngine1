#ifndef COMMAND_ROTATE_CAMERA_H
#define COMMAND_ROTATE_CAMERA_H

#include "Command.h"
#include "ACamera.h"
#include "DataBus.h"
#include "SDL2/SDL.h"
#include "Input.h"

class CommandRotateCamera : public Command
{
public:
    CommandRotateCamera(Input* input, ACamera* camera) : input(input), camera(camera) {}

    void proc(DataBus* dtBus)
    {
        SDL_MouseMotionEvent eventMotion = input->event.motion;
        camera->rotateCamera(eventMotion.xrel, eventMotion.yrel);
    }
private:
    Input* input;
    ACamera* camera;
};

#endif // COMMAND_ESCAPE_H
