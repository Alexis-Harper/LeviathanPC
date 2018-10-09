#include "stdafx.h"
#include "Sprite.h"

#include "ErrorEnum.h"

#include "Input.h"

namespace {

	int screenWidth, screenHeight;
	float cameraX, cameraY;

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

	this->pWidth = w;
	this->pHeight = h;

	this->width = (float) w / 960;
	this->height = (float) h / 740;

}

Sprite::~Sprite () {

	SDL_DestroyTexture (this->texture);

}

void Sprite::updateScreenDimentions (int w, int h) {

	screenWidth = w;
	screenHeight = h;

}

void Sprite::translateCamera (float x, float y) {

	cameraX += x;
	cameraY += y;

}

void Sprite::setCamera (float x, float y) {

	cameraX = x;
	cameraY = y;

}

void Sprite::render (SDL_Renderer *render, float x, float y, float scale, SDL_Rect *clip) {

	SDL_Rect renderQuad = { (int) ((x - cameraX) * screenWidth), (int) ((y + cameraY) * screenHeight), (int) (this->width * screenWidth), (int) (this->height * screenHeight) };

	if (clip != NULL) {

		renderQuad.w = clip->w;
		renderQuad.h = clip->h;

	}

	renderQuad.w = (int) (renderQuad.w * scale);
	renderQuad.h = (int) (renderQuad.h * scale);

	SDL_RenderCopy (render, this->texture, clip, &renderQuad);

}

void Sprite::srender (SDL_Renderer *render, float x, float y, float scale, SDL_Rect *clip) {

	SDL_Rect renderQuad = { (int) (x * screenWidth), (int) (y * screenHeight), (int) (this->width * screenWidth), (int) (this->height * screenHeight) };

	if (clip != NULL) {

		renderQuad.w = clip->w;
		renderQuad.h = clip->h;

	}

	renderQuad.w = (int) (renderQuad.w * scale);
	renderQuad.h = (int) (renderQuad.h * scale);

	SDL_RenderCopy (render, this->texture, clip, &renderQuad);

}

void Sprite::setBlendMode (SDL_BlendMode mode) {

	SDL_SetTextureBlendMode (this->texture, mode);

}

void Sprite::setAlpha (Uint8 alpha) {

	SDL_SetTextureAlphaMod (this->texture, alpha);

	this->alpha = alpha;

}

void Sprite::crescereAlpha (int8_t alpha) {

	this->alpha += alpha;

	SDL_SetTextureAlphaMod (this->texture, this->alpha);

}

void Sprite::crescereAlpha_s (int8_t alpha) {

	if (this->alpha + alpha <= 0) {

		this->alpha = 0;

	} else {

		this->alpha += alpha;

	}

}

float Sprite::getWidth () {

	return this->width;

}

float Sprite::getHeight () {

	return this->height;

}

int Sprite::getPWidth () {

	return this->pWidth;
	
}

int Sprite::getPHeight () {

	return this->pHeight;

}

SpriteSheet::SpriteSheet () {

	//Default constructor

}

SpriteSheet::SpriteSheet (SDL_Renderer *renderer, char *filename, int x, int y) {

	this->sprite = new Sprite (renderer, filename);

	this->imagesX = x;
	this->imagesY = y;

	this->resX = (int) (this->sprite->getPWidth() / x);
	this->resY = (int) (this->sprite->getPHeight() / y);

}

SpriteSheet::~SpriteSheet () {

	delete this->sprite;

}

void SpriteSheet::render (SDL_Renderer *render, float x, float y, float scale, int indexX, int indexY) {

	SDL_Rect clip;

	clip.x = this->resX * indexX;
	clip.y = this->resY * indexY;
	clip.w = this->resX;
	clip.h = this->resY;

	this->sprite->render (render, x, y, scale, &clip);

}

void SpriteSheet::srender (SDL_Renderer *render, float x, float y, float scale, int indexX, int indexY) {

	SDL_Rect clip;

	clip.x = this->resX * indexX;
	clip.y = this->resY * indexY;
	clip.w = this->resX;
	clip.h = this->resY;

	this->sprite->srender (render, x, y, scale, &clip);

}

void SpriteSheet::setBlendMode (SDL_BlendMode mode) {

	this->sprite->setBlendMode (mode);

}

void SpriteSheet::setAlpha (Uint8 alpha) {

	this->sprite->setAlpha (alpha);

}

void SpriteSheet::crescereAlpha (int8_t alpha) {

	this->sprite->crescereAlpha (alpha);

}

void SpriteSheet::crescereAlpha_s (int8_t alpha) {

	this->sprite->crescereAlpha_s (alpha);

}
