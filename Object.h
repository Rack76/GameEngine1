#ifndef OBJECT_H
#define OBJECT_H

#include <GL/glew.h>
#include <vector>
#include "Shader.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/rotate_vector.hpp"


class Object
{
public:
    Object(Shader _shader, float x, float y, float z, float _scale, glm::vec3 _linearVelocity ,glm::vec3 _angularVelocity, glm::vec3 _orientation);
    Object(const Object& object);
    void loadVertices(std::vector<float> verticesTextureArray);
    void rotateZ();
    void setPosition();
    virtual void setCapsule();
    void translate(glm::vec3 vec);
    glm::vec3 position;
    glm::vec3 linearVelocity;
    glm::vec3 angularVelocity;
    glm::vec3 linearAcceleration;
    glm::vec3 angularAcceleration;
    glm::vec3 centerOfMass;
    glm::vec3 XOrientation;
    glm::vec3 YOrientation;
    glm::vec3 ZOrientation;
    glm::vec3 orientation1;
    glm::vec3 orientation2;
    glm::vec3 force;
    glm::vec3 torque;
    Shader shader;
    GLuint vbo;
    glm::mat4 Model;
    float* verticesCoordinates;
    int indicesCount;
    float angleZ;
    float angleY;
    float angleX;
    float scale;
};

inline void Object::setCapsule(){}

#endif // OBJECT_H
