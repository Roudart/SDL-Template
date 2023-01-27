#pragma once
#include <SDL_image.h>

namespace Img {

	struct Image {
		SDL_Rect rect;
		SDL_Texture* texture;
		Image* destroyIfNot = NULL;

		Image() {
			this->rect = SDL_Rect();
			this->texture = NULL;
		};

		Image(SDL_Texture* texture, SDL_Rect rect) {
			this->rect = rect;
			this->texture = texture;
		}

		~Image() {
			if (this->texture != NULL) {
				SDL_DestroyTexture(this->texture);
				this->texture = NULL;
			}
		}
	};

	void SetRenderer(SDL_Renderer* renderer);
	SDL_Renderer* GetRenderer();
	void LoadImage(const char* imagePath, Image& dest);
	SDL_Texture* LoadImageTeture(const char* imagePath);

	// Struct vector to handle X and Y
	struct vector
	{
		float x;
		float y;
	};
}