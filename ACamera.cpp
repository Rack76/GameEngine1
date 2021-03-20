#include "ACamera.h"

ACamera::ACamera(int windowWidth, int windowHeight)
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

ACamera::ACamera(const ACamera& camera)
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
