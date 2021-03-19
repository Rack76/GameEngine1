#ifndef BONE_H
#define BONE_H

#include <string>
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Bone
{
public:
    std::string Name;
    glm::mat4 TransformMatrix;
    //ObjectContainer ??
    Bone* pFrameSibling;
    Bone* pFrameFirstChild;

};

void printHierarchy(Bone* bone)
{
    std::cout << bone.Name;

    if(bone->pFrameSibling != NULL)
    {
        printHierarchy(bone->pFrameSibling);
    }

    if(bone->pFrameFirstChild) != NULL)
    {
        printHierarchy(bone->pFrameFirstChild)
    }
}

#endif // BONE_H
