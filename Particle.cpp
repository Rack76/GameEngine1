#include "Particle.h"
#include <string>
#include <cassert>
#include <iostream>
#define powf(base, power) ((float)pow(base, power))

void Particle::integrate(float duration)
{
    if(inverseMass == 0) return;;



    position = position + linearVelocity * duration;

    forceAccum = glm::vec3(0, 0, 0);
}

void Particle::setDamping(float damping)
{
    this->damping = damping;
}

void Particle::setInverseMass(float inverseMass)
{
    this->inverseMass = inverseMass;
    this->mass = 1/inverseMass;
}

void Particle::setMass(float mass)
{
    this->mass = mass;
    this->inverseMass = 1/mass;
}


