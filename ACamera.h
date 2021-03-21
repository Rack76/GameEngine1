#ifndef ACAMERA_H
#define ACAMERA_H

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class ACamera
{
public:
    ACamera(int windowWidth, int windowHeight);
    ACamera(const ACamera& camera);
    virtual void setCamera()=0;
    virtual void rotateCamera(float xrel, float yrel)=0;
    virtual void translateOrientation(int sens)=0;
    virtual void translateNormal(int sens)=0;
    virtual void translateUp(int sens)=0;

public:

    int m_windowWidth;
    int m_windowHeight;
    float theta;
    float phi;
    glm::vec3 orientation;
    glm::vec3 up;
    glm::vec3 normal;
    glm::vec3 centre;
    glm::vec3 eye;
    glm::mat4 View;
    glm::mat4 Projection;
};

#endif // ACamera_H
