#include "collisionDetection.h"
#include "CapsuleObject.h"
#include <iostream>
#include <cmath>

bool CapsuleIntersect(Capsule& c1, Capsule& c2, glm::vec3& cp1, glm::vec3& cp2)
{
    Line l1 = c1.line;
    Line l2 = c2.line;

    glm::vec3 p = l1.p - l2.p;

    float d = glm::dot(p, l1.d);
    float a = glm::dot(l1.d, l1.d);
    float b = glm::dot(l2.d, l1.d);
    float c = glm::dot(l2.d, l2.d);
    float e = glm::dot(p, l2.d);

    float s = (2 * b  * e - 2 * c * d) / (2 * a * c - 2 * b * b) ;
    float t = (2 * a  * e - 2 * b * d) / (2 * a * c - 2 * b * b) ;

    glm::vec3 closestPoint1 = l1.p + s * l1.d;
    glm::vec3 closestPoint2 = l2.p + t * l2.d;

    if((t > 0 && t < 1) && (s > 0 && s < 1))
    {

        cp1 = closestPoint1;
        cp2 = closestPoint2;
        if(glm::length(closestPoint1 - closestPoint2) < c1.radius + c2.radius)
        {
            return true;
        }
    }

    if(!(t > 0 && t < 1) && (s > 0 && s < 1))
    {
        float length1 = glm::dot(l2.p - l1.p, l1.d / glm::length(l1.d));
        float length2 = glm::dot(l2.p + l2.d - l1.p, l1.d / glm::length(l1.d));
        glm::vec3 point1 = l1.p + length1 * (l1.d / glm::length(l1.d));
        glm::vec3 point2 = l1.p + length2 * (l1.d / glm::length(l1.d));
        if(glm::length(l2.p - point1) <  glm::length(l2.p + l2.d - point2))
        {
           cp1 = closestPoint1;
           cp2 = l2.p;
        }
        else
        {
           cp1 = closestPoint1;
           cp2 = l2.p + l2.d;
        }
    }

    if((t > 0 && t < 1) && !(s > 0 && s < 1))
    {
      float length1 = glm::dot(l1.p - l2.p, l2.d / glm::length(l2.d));
        float length2 = glm::dot(l1.p + l1.d - l2.p, l2.d / glm::length(l2.d));
        glm::vec3 point1 = l2.p + length1 * (l2.d / glm::length(l2.d));
        glm::vec3 point2 = l2.p + length2 * (l2.d / glm::length(l2.d));
        if(glm::length(l1.p - point1) <  glm::length(l1.p + l1.d - point2))
        {
           cp1 = l1.p;
           cp2 = closestPoint2;
        }
        else
        {
           cp1 = l1.p + l1.d;
           cp2 = closestPoint2;
        }
    }

    if(!(t > 0 && t < 1) && !(s > 0 && s < 1))
    {
        glm::vec3 endPoint1 = glm::length(l1.p - closestPoint1) < glm::length((l1.p + l1.d) - closestPoint1) ? l1.p : l1.p + l1.d;
        glm::vec3 endPoint2 = glm::length(l2.p - closestPoint2) < glm::length((l2.p + l2.d) - closestPoint2) ? l2.p : l2.p + l2.d;
        float length1 = glm::dot(endPoint1 - l2.p, l2.d/glm::length(l2.d));
        if(length1 < 0 || length1 > glm::length(l2.d))
        {
            float length2 = glm::dot(endPoint2 - endPoint1, l1.d/glm::length(l1.d));
            cp1 = l1.p + length2 * l1.d;
            cp2 = endPoint2;
        }
        else
        {
            float length2 = glm::dot(endPoint1 - endPoint2, l2.d/glm::length(l2.d));
            cp1 = endPoint1;
            cp2 = l2.p + length2 * l2.d;
        }
        cp1 = endPoint1;
        cp2 = endPoint2;

    }

    return false;
}

void sphereIntersect(Capsule sphere1, Capsule sphere2, glm::vec3& cp1, glm::vec3& cp2)
{
    glm::vec3 vec1 = glm::normalize(sphere2.line.p - sphere1.line.p);
    glm::vec3 vec2 = glm::normalize(sphere1.line.p - sphere2.line.p);

    cp1 = sphere1.line.p + vec1;
    cp2 = sphere2.line.p + vec2;
}





