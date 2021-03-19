#include "Camera.h"

#define RADIAN(degrees) (degrees * (3.14159265359 / 180))


Camera::Camera(int windowWidth, int windowHeight)
{
    m_windowWidth = windowWidth;
    m_windowHeight = windowHeight;
    phi = 0;
    theta = 0;
    orientation = glm::vec3(sin(theta) * cos(phi), sin(phi), cos(phi) * cos(theta));
    up = glm::vec3(0, 1, 0);
    eye = glm::vec3(0, 0, -5);
    centre = eye + orientation;
    normal = glm::cross(orientation, up);
    normal = glm::normalize(normal);
    View = glm::lookAt(eye, centre, up);
    Projection = glm::perspective(70.0, (double)(m_windowWidth / m_windowHeight), 0.01, 200.0);
}

Camera::Camera(const Camera& camera)
{
    theta = camera.theta;
    phi = camera.phi;
    orientation = camera.orientation;
    up = camera.up;
    normal = camera.normal;
    centre = camera.centre;
    eye = camera.eye;
    View = camera.View;
    Projection = camera.Projection;
    m_windowWidth = camera.m_windowWidth;
    m_windowHeight = camera.m_windowHeight;
}

void Camera::setCamera()
{
    orientation = glm::vec3(sin(theta) * cos(phi), sin(phi), cos(phi) * cos(theta));
    centre = eye + orientation;
    normal = glm::cross(orientation, up);
    normal = glm::normalize(normal);
    View = glm::lookAt(eye, centre, up);
    Projection = glm::perspective(70.0, (double)(m_windowWidth / m_windowHeight), 0.01, 200.0);
}

void Camera::rotateCamera(float xrel, float yrel)
{
    theta -= xrel * 0.005;
    phi -= yrel * 0.005;

    if(phi > RADIAN(89))
    {
        phi = RADIAN(89);
    }

    if(phi < RADIAN(-89))
    {
        phi = RADIAN(-89);
    }

    setCamera();
}

void Camera::translateOrientation(int sens)
{
    eye = eye + glm::vec3(orientation.x * 0.05 * sens, orientation.y * 0.05 * sens, orientation.z * 0.05 * sens);
    setCamera();
}

void Camera::translateNormal(int sens)
{
    eye = eye + glm::vec3(normal.x * 0.05 * sens, normal.y * 0.05 * sens, normal.z * 0.05 * sens);
    setCamera();
}

void Camera::translateUp(int sens)
{
    eye = eye + glm::vec3(up.x * 0.05 * sens, up.y * 0.05 * sens, up.z * 0.05 * sens);
    setCamera();
}
