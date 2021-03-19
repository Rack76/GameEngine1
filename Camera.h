#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Camera
{
public:
    Camera(int windowWidth, int windowHeight);
    Camera(const Camera& camera);
    void setCamera();
    void rotateCamera(float xrel, float yrel);
    void translateOrientation(int sens);
    void translateNormal(int sens);
    void translateUp(int sens);
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

#endif // CAMERA_H
