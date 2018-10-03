#pragma once

SDL_Texture* loadTexture (SDL_Renderer *renderer, char *filename);

//Renders SDL Sprite 
class Sprite {

public:

	Sprite ();
	Sprite (SDL_Renderer *renderer, char *filename);
	~Sprite ();

	static void updateScreenDimentions (int x, int y);
	static void translateCamera (float x, float y);
	static void setCamera (float x, float y);

	//Render with camera
	void render (SDL_Renderer *renderer, float x, float y, float scale, SDL_Rect *clip);
	//Render without camera
	void srender (SDL_Renderer *renderer, float x, float y, float scale, SDL_Rect *clip);

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
	SpriteSheet (SDL_Renderer *renderer, char *filename, int w, int h);
	~SpriteSheet ();

	//Render with camera
	void render (SDL_Renderer *renderer, float x, float y, float scale, int indexX, int indexY);
	//Render without camera
	void srender (SDL_Renderer *renderer, float x, float y, float scale, int indexX, int indexY);

private:

	Sprite *sprite;

	int imagesX, imagesY, resX, resY;

};
