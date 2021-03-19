#ifndef CAPSULEOBJECT_H
#define CAPSULEOBJECT_H

#include "Object.h"
#include "collisionDetection.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>

#define RADIAN(degrees) (degrees * (3.14159265359 / 180))

struct capsuleShape
{

};

class CapsuleObject : public Object
{
public:

    glm::mat4 rotationMatrix;
    Capsule capsule;
        float mass;
    glm::mat3 inertiaTensor;
    float damping;

    CapsuleObject(Shader shader, float x, float y, float z, glm::vec3 linearVelocity, glm::vec3 _angularVelocity, glm::vec3 _orientation) : Object(shader, x,  y,  z, 1,linearVelocity, _angularVelocity, _orientation)
    {
        XOrientation = glm::vec3(1, 0, 0);
        YOrientation = glm::vec3(0, 1, 0);
        ZOrientation = glm::vec3(0, 0, 1);
        capsule.line.p = glm::vec3(0, -2, 0);
        capsule.line.d = glm::vec3(0, 4, 0);
        capsule.radius = 0.1;
        mass = 4;
        damping = 0;
    }

    CapsuleObject(const CapsuleObject& co) : Object(co)
    {
        rotationMatrix = co.rotationMatrix;
        capsule = co.capsule;
        mass = co.mass;
        inertiaTensor = co.inertiaTensor;
    }

    virtual void setCapsule(float dt)
    {
        rotationMatrix = glm::mat4(1, 0, 0, 0,
                                0, 1, 0, 0,
                                0, 0, 1 ,0 ,
                                0, 0, 0, 1);
        capsule.line.p = glm::vec3(0, -2, 0);
        capsule.line.d = glm::vec3(0, 4, 0);
        calculateCapsuleInertia();
        integrate(dt);
        rotate();
        translate();
    }

    virtual void rotateAndTranslateCapsule()
    {
        rotationMatrix = glm::mat4(1, 0, 0, 0,
                                0, 1, 0, 0,
                                0, 0, 1 ,0 ,
                                0, 0, 0, 1);
        capsule.line.p = glm::vec3(0, -2, 0);
        capsule.line.d = glm::vec3(0, 4, 0);
        rotate();
        translate();
    }

    virtual void translate()
    {
        capsule.line.p = position - capsule.line.d * 0.5f;
    }

    virtual void rotate()
    {
        capsule.line.p = glm::rotate(capsule.line.p , orientation2.x , glm::vec3(1.0, 0, 0));
        capsule.line.p = glm::rotate(capsule.line.p , orientation2.y , glm::vec3(0, 1, 0));//TC
        capsule.line.p = glm::rotate(capsule.line.p , orientation2.z , glm::vec3(0, 0, 1));
        capsule.line.d = -2.0f * capsule.line.p;
        rotationMatrix = glm::rotate(rotationMatrix ,orientation2.x , glm::vec3(1, 0, 0)); //TC
        rotationMatrix = glm::rotate(rotationMatrix ,orientation2.y , glm::vec3(0, 1, 0)); //TC
        rotationMatrix = glm::rotate(rotationMatrix ,orientation2.z , glm::vec3(0, 0, 1)); //TC
    }

    void calculateCapsuleInertia()
    {
        glm::mat3 R = rotationMatrix;

        glm::mat3 inertiaTensorAtCenterOfMass = glm::mat3(18, 0, 0,
                                            0, 0.2, 0,
                                            0, 0, 18);

        glm::mat3 inverseR = glm::inverse(R);

        inertiaTensor = R * inertiaTensorAtCenterOfMass * inverseR;
    }

    void integrate(float dt)
    {
        damping += dt;
        calculateCapsuleInertia();
        linearAcceleration = force * 1.0f/mass;
        angularAcceleration = glm::mat3(18, 0, 0,
                                        0, 0.2, 0,
                                        0, 0, 18) * torque;
        linearVelocity += linearAcceleration * dt;
        linearVelocity *= powf(0.99, damping);
        angularVelocity += angularAcceleration * dt;
        angularVelocity *= powf(0.80, damping);
        position += linearVelocity * dt;
        orientation2 += angularVelocity * dt;
        force = glm::vec3(0, 0, 0);
        angularAcceleration = glm::vec3(0, 0, 0);
        linearAcceleration = glm::vec3(0, 0, 0);
    }
};

#endif // CAPSULEOBJECT_H
