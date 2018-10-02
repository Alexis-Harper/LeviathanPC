#pragma once

SDL_Texture* loadTexture (SDL_Renderer*, char*);

//Renders SDL Sprite 
class Sprite {

public:

	Sprite ();
	Sprite (SDL_Renderer*, char*);
	~Sprite ();

	static void updateScreenDimentions (int, int);

	void render (SDL_Renderer*, float, float, float, SDL_Rect*);

	float getWidth ();
	float getHeight ();

	int getPWidth ();
	int getPHeight ();

private:

	SDL_Texture *texture;

	float width, height;
	int pWidth, pHeight;

};

//Automatically parses spritesheet and renders it
class SpriteSheet {

public:

	SpriteSheet ();
	SpriteSheet (SDL_Renderer*, char*, int, int);
	~SpriteSheet ();

	void render (SDL_Renderer*, float, float, float, int, int);

private:

	Sprite *sprite;

	int imagesX, imagesY, resX, resY;

};
