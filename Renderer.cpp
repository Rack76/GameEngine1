#include "GL/glew.h"
#include "Renderer.h"
#include "Globals.h"

void Renderer::draw(int i)
{
    glUseProgram(worldObject[i]->shader.programID);
    glBindBuffer(GL_ARRAY_BUFFER, worldObject[i]->vbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 20, (const void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 20, (const void*)12);
    worldObject[i]->setPosition();
    comboMatrix = actualCamera->Projection * actualCamera->View * worldObject[i]->Model;
    glUniformMatrix4fv(glGetUniformLocation(worldObject[i]->shader.programID, "comboMatrix"), 1, GL_FALSE, glm::value_ptr(comboMatrix));
    glDrawArrays(GL_TRIANGLES, 0, worldObject[i]->indicesCount);
}

void Renderer::drawIndex(int i, unsigned int arrayB[])
{

}
