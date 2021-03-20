#include "Window.h"
#include "Object.h"
#include "MeshLoader.h"
#include "Globals.h"
#include "Camera.h"
#include "TextureImageLoader.h"
#include "Shader.h"
#include "Renderer.h"
#include "collisionDetection.h"
#include "CapsuleObject.h"
#include "Input.h"
#include <iostream>
#include <cmath>

#define RADIAN(degrees) (degrees * (3.14159265359 / 180))
#define g 9.8

std::vector<Object*> worldObject;
Camera actualCamera(640, 480);

    bool CAMERA_MOVE_FORWARD = false;
    bool CAMERA_MOVE_BACKWARD = false;
    bool CAMERA_MOVE_LEFT = false;
    bool CAMERA_MOVE_RIGHT = false;
    bool CAMERA_MOVE_UP = false;
    bool CAMERA_MOVE_DOWN = false;
    bool ROTATE_OBJECT_Z = false;
    bool WINDOW_QUIT = false;

    SDL_Event event;

bool conservativeAdvancement(CapsuleObject capsule1, CapsuleObject capsule2, float dt, float& TOC, int maximumIterations);
void contactQueries(CapsuleObject* capsule1, CapsuleObject* capsule2, glm::vec3& contactPoint, glm::vec3& force1, glm::vec3& force2);
void closestPointsCapsules(CapsuleObject* capsule1, CapsuleObject* capsule2, glm::vec3& cp1, glm::vec3& cp2);
void applyCollisionForce(glm::vec3 contactPoint, glm::vec3 force, Object* object);
bool conservativeAdvancementSphere(CapsuleObject capsule1, CapsuleObject capsule2, float dt, float& TOC, int maximumIterations);
void contactQueriesSphere(CapsuleObject* capsule1, CapsuleObject* capsule2, glm::vec3& contactPoint, glm::vec3& force1, glm::vec3& force2);

void updateWorld(float duration)
{
       if(CAMERA_MOVE_FORWARD)
       {
           actualCamera.translateOrientation(1);
       }
       if(CAMERA_MOVE_BACKWARD)
       {
           actualCamera.translateOrientation(-1);
       }
       if(CAMERA_MOVE_RIGHT)
       {
           actualCamera.translateNormal(1);
       }
       if(CAMERA_MOVE_LEFT)
       {
           actualCamera.translateNormal(-1);
       }
       if(CAMERA_MOVE_UP)
       {
           actualCamera.translateUp(1);
       }
       if(CAMERA_MOVE_DOWN)
       {
           actualCamera.translateUp(-1);
       }
       if(ROTATE_OBJECT_Z)
       {
          static_cast<CapsuleObject*>(worldObject[1])->damping = 0.9;
          worldObject[1]->linearVelocity = glm::vec3(-2, 0, 0);
       }

    glm::vec3 contactNormal1, contactPoint, contactNormal2;
    float TOC;

    CapsuleObject* capsule1 = static_cast<CapsuleObject*>(worldObject[0]);
    CapsuleObject* capsule2 = static_cast<CapsuleObject*>(worldObject[1]);

    if(conservativeAdvancement(*capsule1, *capsule2, duration, TOC, 7))
    {
        capsule1->setCapsule(TOC);
        capsule2->setCapsule(TOC);
        contactQueries(capsule1, capsule2, contactPoint, contactNormal1, contactNormal2);
        applyCollisionForce(contactPoint, contactNormal1, capsule1);
        applyCollisionForce(contactPoint, contactNormal2, capsule2);
        capsule1->damping = 0.9;
        capsule2->damping = 0.9;
    }

    capsule1->setCapsule(duration);
    capsule2->setCapsule(duration);


}

void generateOutout(Renderer& renderer, Window& window)
{
        for(int i = 0; i < worldObject.size(); i++)
        {
            renderer.draw(i);
        }

        window.render();
}

int main(int argc, char **argv)
{
    Window window(1000, 500, 640, 480);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_SetRelativeMouseMode(SDL_TRUE);

     glewInit();

     glViewport(0, 0, 640, 640);
     glEnable(GL_DEPTH_TEST);

    Shader shader;
    shader.parseCreateAndCompileShader("basic.shader");

    Shader shader2;
    shader2.parseCreateAndCompileShader("color.shader");

    TextureImageLoader textureImageLoader;
    textureImageLoader.loadImage("texture1.jpg", GL_TEXTURE0);

    MeshLoader meshLoader;
    meshLoader.loadOBJFile("newCapsule.obj");

    MeshLoader meshLoader1;
    meshLoader1.loadOBJFile("icoSphere.obj");

    Renderer renderer;

    Renderer renderer2;

    worldObject.push_back(new CapsuleObject(shader, -0.5, 0, 0, glm::vec3(0, 0.0, 0), glm::vec3(0, 0, 0), glm::vec3(RADIAN(90), 0, 0)));
    worldObject[0]->loadVertices(meshLoader.verticeTextureArray);

    worldObject.push_back(new CapsuleObject(shader2, 0, 0, 0, glm::vec3(-0.5, 0, 0.0),glm::vec3(0,0,0) ,glm::vec3(0 , 0 , 0)));
    worldObject[1]->loadVertices(meshLoader.verticeTextureArray);

    static_cast<CapsuleObject*>(worldObject[0])->setCapsule(0);
    static_cast<CapsuleObject*>(worldObject[1])->setCapsule(0);

    Input input;

    glm::vec3 cp1;
    glm::vec3 cp2;

    int temp, duration;

    while(!WINDOW_QUIT)
    {

       input.getInput();

       static int lastTime = 0;
       static int firstTime = SDL_GetTicks();
       temp = lastTime;
       lastTime = SDL_GetTicks() - firstTime;
       duration = lastTime - temp;


       updateWorld((float)duration/1000);

       generateOutout(renderer2, window);

    }

    window.cleanUp();

    return 0;
}

 void closestPointsCapsules(CapsuleObject* capsule1, CapsuleObject* capsule2, glm::vec3& cp1, glm::vec3& cp2)
{
        glm::vec3 temp1, temp2;
        CapsuleIntersect(capsule1->capsule, capsule2->capsule, temp1, temp2);
        cp1 = temp1 + ((temp2 - temp1)/glm::length(temp2 - temp1)) * 0.1f;
        cp2 = temp2 + ((temp1 - temp2)/glm::length(temp1 - temp2)) * 0.1f;
}

void contactQueries(CapsuleObject* capsule1, CapsuleObject* capsule2, glm::vec3& contactPoint, glm::vec3& force1, glm::vec3& force2)
{
    glm::vec3 temp1, temp2;
    CapsuleIntersect(capsule1->capsule, capsule2->capsule, temp1, temp2);
    contactPoint = temp1 + (temp2 - temp1) * 0.5f;
    glm::vec3 contactNormal1 =  -(contactPoint - temp1) / glm::length(contactPoint - temp1);
    glm::vec3 contactNormal2 =  -(contactPoint - temp2) / glm::length(contactPoint - temp2);
    force1 = contactNormal1 * 5.0f;
    force2 = contactNormal2 * 5.0f;
}

bool conservativeAdvancementSphere(CapsuleObject capsule1, CapsuleObject capsule2, float dt, float& TOC, int maximumIterations)
{
    float deltaT;
    glm::vec3 cp1, cp2;
    float t = 0;
    float temp;
    int iterations = 0;
    float denom;



    while(1)
    {

        sphereIntersect(capsule1.capsule, capsule2.capsule, cp1, cp2);

        float distance = glm::length(cp1 - cp2);

        if((capsule1.angularVelocity) == glm::vec3(0, 0, 0) &&
           (capsule2.angularVelocity) == glm::vec3(0, 0, 0) &&
           (capsule1.linearVelocity) == glm::vec3(0, 0, 0) &&
           (capsule2.linearVelocity) == glm::vec3(0, 0, 0))
        {
            return false;
        }



        denom = glm::dot(capsule1.linearVelocity - capsule2.linearVelocity, (cp2 - cp1) / distance)
 + glm::length(capsule1.angularVelocity) + glm::length(capsule2.angularVelocity);

       if(distance < 0.2001)
        {
            TOC = t;
            return true;
        }

        deltaT = (distance / denom);

        if(deltaT < 0)
        {
            return false;
        }

        t += deltaT;

        if(t > dt)
        {
            return false;
        }

        if(iterations >= maximumIterations)
        {
            TOC = t;
            return true;
        }

        capsule1.position += capsule1.linearVelocity * 0.5f *deltaT;
        capsule2.position += capsule2.linearVelocity * 0.5f * deltaT;

        capsule1.orientation2 += capsule1.angularVelocity * 0.5f * deltaT;
        capsule2.orientation2 += capsule2.angularVelocity * 0.5f * deltaT;

        capsule1.rotateAndTranslateCapsule();
        capsule2.rotateAndTranslateCapsule();

        ++iterations;
    }
}

bool conservativeAdvancement(CapsuleObject capsule1, CapsuleObject capsule2, float dt, float& TOC, int maximumIterations)
{
    float deltaT;
    glm::vec3 cp1, cp2;
    float oldT = 0;
    float t = 0;
    float temp;
    int iterations = 0;
    float denom;
    glm::vec3 sc1, sc2;


    while(1)
    {
        closestPointsCapsules(&capsule1, &capsule2, cp1, cp2);

        CapsuleIntersect(capsule1.capsule, capsule2.capsule, sc1, sc2);

        float distance = glm::length(cp1 - cp2);

        if(glm::length(sc1-sc2) < 0.2001)
        {
             std::cout << "old" << std::endl;
            TOC = oldT;
            return true;
        }

        denom = glm::dot(capsule1.linearVelocity - capsule2.linearVelocity, (cp2 - cp1) / distance)
 + glm::length(capsule1.angularVelocity) * 2 + glm::length(capsule2.angularVelocity) * 2;


        deltaT =  0.5 * (distance / denom);

        if(deltaT < 0)
        {
            return false;
        }

        oldT = t;

        t += deltaT;

        if(t > dt)
        {
            return false;
        }

        if(iterations >= maximumIterations)
        {
            TOC = t;
            return true;
        }


        capsule1.position += capsule1.linearVelocity * deltaT;
        capsule2.position += capsule2.linearVelocity * deltaT;

        capsule1.orientation2 += capsule1.angularVelocity * deltaT;
        capsule2.orientation2 += capsule2.angularVelocity * deltaT;

        capsule1.rotateAndTranslateCapsule();
        capsule2.rotateAndTranslateCapsule();

        ++iterations;
    }
}

void contactQueriesSphere(CapsuleObject* capsule1, CapsuleObject* capsule2, glm::vec3& contactPoint, glm::vec3& force1, glm::vec3& force2)
{
    glm::vec3 temp1, temp2;
    sphereIntersect(capsule1->capsule, capsule2->capsule, temp1, temp2);
    glm::vec3 contactNormal1 =  -(temp1 - capsule1->position) / glm::length(temp1 - capsule1->position);
    glm::vec3 contactNormal2 =  -(temp1 - capsule2->position) / glm::length(temp1 - capsule2->position);
    contactPoint = temp1;
    force1 = contactNormal1 * 2.0f;
    force2 = contactNormal2 * 2.0f;
}

void applyCollisionForce(glm::vec3 contactPoint, glm::vec3 force, Object* object)
{
    object->linearVelocity = - object->linearVelocity;
    object->angularVelocity = - object->angularVelocity;
    object->force = 10.0f * force;
    object->torque = glm::cross(contactPoint - object->position, force );
}

