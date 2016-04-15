#ifndef EXTENDED_TEXTURE_H
#define EXTENDED_TEXTURE_H

#include <SDL.h>
#include <SDL_ttf.h>

#include <iostream>

#include "gamefwd.h"

class ExtendedTexture {
public:
    ExtendedTexture();
    ~ExtendedTexture();

    bool loadFromFile(SDL_Renderer*, std::string path);
    bool loadFromRenderedText(TTF_Font *gFont, std::string textureText, SDL_Color textColor );

    void free();

    void render(int x, int y, SDL_Rect* clip = NULL);

    int getWidth();
    int getHeight();

private:
    SDL_Texture* mTexture;

    int mWidth;
    int mHeight;
};

#endif // EXTENDED_TEXTURE_H
