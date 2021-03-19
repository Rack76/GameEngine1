#ifndef PARTICLE_H
#define PARTICLE_H

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Object.h"

class Particle : public Object
{
public:

Particle(Shader shader, float x, float y, float z, glm::vec3 _angularVelocity, glm::vec3 _orientation) : Object(shader,  x,  y,  z, 1, glm::vec3(0, 0, 0), _angularVelocity, _orientation)
{
    setMass(1);
    setDamping(0.73);
}
void setMass(float mass);
void setInverseMass(float inverseMass);
void setDamping(float damping);
void integrate(float duration);

protected:
    glm::vec3 forceAccum;
    float damping;
    float mass;
    float inverseMass;
};

#endif // PARTICULE_H
