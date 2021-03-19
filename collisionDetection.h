#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"


class Line
{
public:
    glm::vec3 p;
    glm::vec3 d;
};

class Capsule
{
public:
    Line line;
    float radius;
};


void sphereIntersect(Capsule sphere1, Capsule sphere2, glm::vec3& cp1, glm::vec3& cp2);
bool CapsuleIntersect(Capsule& c1, Capsule& c2, glm::vec3& cp1, glm::vec3& cp2);

#endif // COLLISIONDETECTION_H
