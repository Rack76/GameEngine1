#include "Input.h"

void Input::getInput()
{

        while(SDL_PollEvent(&event))              //inputHandling
        {
            switch(event.type)
            {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    WINDOW_QUIT = true;
                    break;
                case SDLK_z:
                    CAMERA_MOVE_FORWARD = true;
                    break;
                case SDLK_s:
                    CAMERA_MOVE_BACKWARD = true;
                    break;
                case SDLK_q:
                    CAMERA_MOVE_LEFT = true;
                    break;
                case SDLK_d:
                    CAMERA_MOVE_RIGHT = true;
                    break;
                case SDLK_SPACE:
                    CAMERA_MOVE_UP = true;
                    break;
                case SDLK_LSHIFT:
                    CAMERA_MOVE_DOWN = true;
                    break;
                case SDLK_r:
                    ROTATE_OBJECT_Z = true;
                    break;
                case SDLK_LEFT:

                    break;
                case SDLK_RIGHT:

                    break;
                case SDLK_UP:

                    break;
                case SDLK_DOWN:

                    break;
                }
            break;

            case SDL_KEYUP:
                switch(event.key.keysym.sym)
                {
                case SDLK_z:
                    CAMERA_MOVE_FORWARD = false;
                    break;
                case SDLK_s:
                    CAMERA_MOVE_BACKWARD = false;
                    break;
                case SDLK_q:
                    CAMERA_MOVE_LEFT = false;
                    break;
                case SDLK_d:
                    CAMERA_MOVE_RIGHT = false;
                    break;
                case SDLK_SPACE:
                    CAMERA_MOVE_UP = false;
                    break;
                case SDLK_LSHIFT:
                    CAMERA_MOVE_DOWN = false;
                    break;
                case SDLK_r:
                    ROTATE_OBJECT_Z = false;
                    break;
                }
            break;
            }

            switch(event.motion.type)
            {
            case SDL_MOUSEMOTION:
                actualCamera.rotateCamera(event.motion.xrel, event.motion.yrel);
                break;
            }
        }
}
