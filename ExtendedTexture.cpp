#include "ExtendedTexture.h"

#include <stdio.h>

ExtendedTexture::ExtendedTexture() {
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

ExtendedTexture::~ExtendedTexture() {
    free();
}

bool ExtendedTexture::loadFromFile(SDL_Renderer *renderer, std::string path) {
    /*Get rid of existing texture */
    free();

    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
    if (loadedSurface == NULL) {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), SDL_GetError() );
    } else {
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

        if( newTexture == NULL ) {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else {
            /* Get image dimensions */
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        SDL_FreeSurface(loadedSurface);
    }
    mTexture = newTexture;
    return mTexture != NULL;
}

void ExtendedTexture::free() {
    if (mTexture != NULL) {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;

        mWidth = 0;
        mHeight = 0;
    }
}

void ExtendedTexture::render(SDL_Renderer *renderer, int x, int y, SDL_Rect* clip) {
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    //Set clip rendering dimensions
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopy(renderer, mTexture, clip, &renderQuad );
}

int ExtendedTexture::getWidth()
{
    return mWidth;
}

int ExtendedTexture::getHeight()
{
    return mHeight;
}
