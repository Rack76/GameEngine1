#include "TextureImageLoader.h"

void TextureImageLoader::loadImage(std::string textureImagePath, GLenum textureEnum)
{
    glGenTextures(1, &texture);
    glActiveTexture(textureEnum);
    glBindTexture(GL_TEXTURE_2D, texture);
    SDL_Surface* surface;
    surface = IMG_Load(textureImagePath.c_str());
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
