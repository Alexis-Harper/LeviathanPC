#include "stdafx.h"
#include "Sprite.h"

#include "ErrorEnum.h"

#include "Input.h"

namespace {

	int screenWidth, screenHeight;

};

SDL_Texture* loadTexture (SDL_Renderer *renderer, char *filename) {

	SDL_Texture *texture = NULL;

	SDL_Surface *surface = SDL_LoadBMP(filename);

	if (surface == NULL) {

		std::cout << "[-] SDL: " << SDL_GetError () << "\n";

		exit (ERROR_SDL_TEXTURE_LOAD_SURFACE);

	}

	texture = SDL_CreateTextureFromSurface (renderer, surface);

	if (texture == NULL) {

		std::cout << "[-] SDL: " << SDL_GetError () << "\n";

		exit (ERROR_SDL_TEXTURE_LOAD_TEXTURE);

	}

	return texture;

}

Sprite::Sprite () {

	//Default constructor

}

Sprite::Sprite (SDL_Renderer *renderer, char *filename) {

	this->texture = loadTexture (renderer, filename);

	int w, h;

	SDL_QueryTexture (this->texture, NULL, NULL, &w, &h);

	this->width = (float) w / screenWidth;
	this->height = (float) h / screenHeight;

}

Sprite::~Sprite () {

	SDL_DestroyTexture (this->texture);

}

void Sprite::updateScreenDimentions (int w, int h) {

	screenWidth = w;
	screenHeight = h;

}

void Sprite::render (SDL_Renderer *render, float x, float y, float scale, SDL_Rect *clip) {

	SDL_Rect renderQuad = { (int) (x * screenWidth), (int) (y * screenHeight), (int) (this->width * screenWidth), (int) (this->height * screenHeight) };

	if (clip != NULL) {

		renderQuad.w = clip->w;
		renderQuad.h = clip->h;

	}

	renderQuad.w = (int) (renderQuad.w * scale);
	renderQuad.h = (int) (renderQuad.h * scale);

	SDL_RenderCopy (render, this->texture, clip, &renderQuad);

}

float Sprite::getWidth () {

	return this->width;

}

float Sprite::getHeight () {

	return this->height;

}

SpriteSheet::SpriteSheet () {

	//Default constructor

}

SpriteSheet::SpriteSheet (SDL_Renderer *renderer, char *filename, int x, int y) {

	this->sprite = Sprite (renderer, filename);

	this->imagesX = x;
	this->imagesY = y;

	this->resX = this->sprite.getWidth() / x;
	this->resY = this->sprite.getHeight() / y;

}

SpriteSheet::~SpriteSheet () {

	this->sprite.~Sprite ();

}

void SpriteSheet::render (SDL_Renderer *render, float x, float y, float scale, int indexX, int indexY) {

	SDL_Rect clip;

	clip.x = this->resX * indexX;
	clip.y = this->resY * indexY;
	clip.w = this->resX;
	clip.h = this->resY;

	this->sprite.render (render, x, y, scale, &clip);

}
