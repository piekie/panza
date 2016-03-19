#include <SDL.h>
#include <iostream>

#include "gamefwd.h"

#ifndef EXTENDED_TEXTURE_H
#define EXTENDED_TEXTURE_H

class ExtendedTexture {
public:
    ExtendedTexture();
    ~ExtendedTexture();

    bool loadFromFile(SDL_Renderer*, std::string path);

    void free();

    void render(SDL_Renderer*, int x, int y, SDL_Rect* clip = NULL);

    int getWidth();
    int getHeight();

private:
    SDL_Texture* mTexture;

    int mWidth;
    int mHeight;
};

#endif // EXTENDED_TEXTURE_H
