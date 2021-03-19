#include "Object.h"
#include <iostream>
#define RADIAN(degrees) (degrees * (3.14159265359 / 180))

Object::Object(Shader _shader, float x, float y, float z, float _scale, glm::vec3 _linearVelocity ,glm::vec3 _angularVelocity, glm::vec3 _orientation)
{
    shader = _shader;
    scale = _scale;
    angleZ = 0;
    angleX = 0;
    angleY = 0;
    glGenBuffers(1, &vbo);
    Model = glm::mat4(1.0);
    verticesCoordinates = new float[200000];
    position = glm::vec3(x, y, z);
    linearVelocity = _linearVelocity;
    angularVelocity = _angularVelocity;
    linearAcceleration = glm::vec3(0, 0, 0);
    angularAcceleration = glm::vec3(0, 0, 0);
    force = glm::vec3(0,0, 0);
    torque = glm::vec3(0, 0, 0);
    orientation2 = _orientation;
}

Object::Object(const Object& object)
{
    angleX = object.angleX;
    angleZ = object.angleZ;
    vbo = object.vbo;
    Model = object.Model;
    verticesCoordinates = object.verticesCoordinates;
    indicesCount = object.indicesCount;
    position = object.position;
    orientation2 = object.orientation2;
    angularVelocity = object.angularVelocity;
    linearVelocity = object.linearVelocity;
    linearAcceleration = object.linearAcceleration;
    angularAcceleration = object.angularAcceleration;
    force = object.force;
    torque = object.torque;
    shader = object.shader;
}

void Object::loadVertices(std::vector<float> verticesTextureArray)
{
    indicesCount = verticesTextureArray.size()/5;
    for(int i = 0; i < verticesTextureArray.size(); i++)
    {
        verticesCoordinates[i] = verticesTextureArray[i];
    }
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 4 * verticesTextureArray.size(), verticesCoordinates, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 20, (const void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 20, (const void*)12);
}

void Object::setPosition()
{
    Model = glm::mat4(1.0);
    Model = glm::translate(Model, position);
    Model = glm::rotate(Model, orientation2.z, glm::vec3(0, 0, 1));
    Model = glm::rotate(Model, orientation2.y, glm::vec3(0, 1, 0));
    Model = glm::rotate(Model, orientation2.x, glm::vec3(1, 0, 0));
    Model = glm::scale(Model, glm::vec3(scale, scale, scale));
}

void Object::rotateZ()
{
    Model = glm::rotate(Model, (float)RADIAN(1), glm::vec3(0, 0, 1));
}

void Object::translate(glm::vec3 vec)
{

    centerOfMass += vec;
}
