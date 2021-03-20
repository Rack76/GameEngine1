#include "Input.h"

    bool CAMERA_MOVE_FORWARD = false;
    bool CAMERA_MOVE_BACKWARD = false;
    bool CAMERA_MOVE_LEFT = false;
    bool CAMERA_MOVE_RIGHT = false;
    bool CAMERA_MOVE_UP = false;
    bool CAMERA_MOVE_DOWN = false;
    bool ROTATE_OBJECT_Z = false;
    bool WINDOW_QUIT = false;

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

                    break;
                case SDLK_s:

                    break;
                case SDLK_q:

                    break;
                case SDLK_d:

                    break;
                case SDLK_SPACE:

                    break;
                case SDLK_LSHIFT:

                    break;
                case SDLK_r:

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

                    break;
                case SDLK_s:

                    break;
                case SDLK_q:

                    break;
                case SDLK_d:

                    break;
                case SDLK_SPACE:

                    break;
                case SDLK_LSHIFT:
                    break;
                case SDLK_r:

                    break;
                }
            break;
            }

            switch(event.motion.type)
            {
            case SDL_MOUSEMOTION:
                camera->rotateCamera(event.motion.xrel, event.motion.yrel);
                break;
            }
        }
}
