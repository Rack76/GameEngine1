#ifndef CHARACTER_H
#define CHARACTER_H

#include "Object.h"

class Character : public Object
{
public:
    glm::mat4 Pose;
};

#endif // CHARACTER_H
