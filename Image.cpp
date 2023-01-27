#include "image.h"

namespace Img {
    SDL_Renderer* SDL_RENDERER;
}

SDL_Texture* Img::LoadImageTeture(const char* imagePath) {
    SDL_Surface* tmpSurface = IMG_Load(imagePath);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(SDL_RENDERER, tmpSurface);
    SDL_FreeSurface(tmpSurface);

    return texture;
}

void Img::LoadImage(const char* imagePath, Image &dest) {
    SDL_Surface* tmpSurface = IMG_Load(imagePath);

    dest.texture = SDL_CreateTextureFromSurface(SDL_RENDERER, tmpSurface);
    dest.rect = tmpSurface->clip_rect;

    SDL_FreeSurface(tmpSurface);
}

void Img::SetRenderer(SDL_Renderer* renderer) {
    SDL_RENDERER = renderer;
}


SDL_Renderer* Img::GetRenderer() {
    return SDL_RENDERER;
}
