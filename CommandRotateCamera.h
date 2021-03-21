#ifndef COMMAND_ROTATE_CAMERA_H
#define COMMAND_ROTATE_CAMERA_H

#include "Command.h"
#include "ACamera.h"
#include "DataBus.h"
#include "SDL2/SDL.h"

class CommandRotateCamera : public Command
{
public:
    void proc(DataBus* dtBus)
    {
        ACamera* camera = (ACamera*)dtBus->data.at("camera");
        SDL_MouseMotionEvent eventMotion = *(SDL_MouseMotionEvent*)dtBus->data.at("eventMotion");
        camera->rotateCamera(eventMotion.x, eventMotion.y);
    }
};

#endif // COMMAND_ESCAPE_H
