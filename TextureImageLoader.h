#ifndef TEXTUREIMAGELOADER_H
#define TEXTUREIMAGELOADER_H

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class TextureImageLoader
{
public:
    void loadImage(std::string textureImagePath, GLenum textureEnum);
    GLuint texture;
};

#endif // TEXTUREIMAGELOADER_H
