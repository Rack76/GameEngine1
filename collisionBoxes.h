#ifndef COLLISIONBOXES_H
#define COLLISIONBOXES_H

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Sphere
{
public:
    bool collides(Cube&);
    float radius;
};

class Cube
{
public:
    bool collides(Sphere&);
};

#endif // COLLISIONBOXES_H
