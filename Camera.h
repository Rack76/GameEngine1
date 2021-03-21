#ifndef CAMERA_H
#define CAMERA_H

#include "ACamera.h"

class Camera : public ACamera
{
public:
    Camera(int windowWidth, int windowHeight) : ACamera(windowWidth, windowHeight)
    {

    }

    Camera(const Camera& camera) : ACamera(camera)
    {

    }

    void setCamera();
    void rotateCamera(float xrel, float yrel);
    void translateOrientation(int sens);
    void translateNormal(int sens);
    void translateUp(int sens);
};

#endif // CAMERA_H
