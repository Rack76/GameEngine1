#ifndef RENDERER_H
#define RENDERRE_H

#include "Shader.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Renderer
{
   public:
       void draw(int i);
       void drawIndex(int i, unsigned int arrayB[]);
       Shader m_shader;
       glm::mat4 comboMatrix;
};

#endif // RENDERER_H
