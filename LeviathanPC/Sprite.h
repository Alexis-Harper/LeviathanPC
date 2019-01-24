#pragma once

/**
 * Author:    Alexis Harper
 * Created:   16.09.2018
 *
 * Description: Sprites is a class that does all the image loading and
 *              rendering for SDL_gpu (previously SDL). 
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 **/

//Loads up image from file to GPU_Image
GPU_Image* loadTexture (char *filename);

//Renders SDL Sprite 
class Sprite {

public:

	Sprite ();
	Sprite (char *filename);
	~Sprite ();

	//Call on window size change to correct movement
	static void updateScreenDimentions (float x, float y);
	//Translate camera position
	static void translateCamera (float x, float y);
	//Set camera position
	static void setCamera (float x, float y);

	//Render with camera
	void render (GPU_Target *screen, float x, float y, float scale, GPU_Rect *clip);
	//Render without camera
	void srender (GPU_Target *screen, float x, float y, float scale, GPU_Rect *clip);

	//Set blending
	void setBlendMode (GPU_BlendPresetEnum mode);
	//Set filter
	void setFilter (GPU_FilterEnum filter);
	//Set color blend
	void setColor (Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);
	//Set alpha
	void setAlpha (Uint8 alpha);

	//Increment or decrement (crescere) alpha value
	void crescereAlpha (int8_t alpha);
	//Increment or decrement (crescere) alpha value (with safety of negatives replaced with 0)
	void crescereAlpha_s (int8_t alpha);

	//Get screen dimentions
	float getWidth ();
	float getHeight ();

	//Get image dimentions
	int getPWidth ();
	int getPHeight ();

private:

	//GPU_Image object pointer
	GPU_Image *texture;

	//Dimentions
	float width, height;
	int pWidth, pHeight;

	//Alpha value
	int alpha;

};

//Automatically parses spritesheet and renders it
class SpriteSheet {

public:

	SpriteSheet ();
	SpriteSheet (char *filename, int w, int h);
	~SpriteSheet ();

	//Render with camera
	void render (GPU_Target *screen, float x, float y, float scale, int indexX, int indexY);
	//Render without camera
	void srender (GPU_Target *screen, float x, float y, float scale, int indexX, int indexY);

	//Set blending
	void setBlendMode (GPU_BlendPresetEnum mode);
	//Set filter
	void setFilter (GPU_FilterEnum filter);
	//Set color blend
	void setColor (Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);
	//Set alpha
	void setAlpha (Uint8 alpha);

	//Increment or decrement (crescere) alpha value
	void crescereAlpha (int8_t alpha);
	//Increment or decrement (crescere) alpha value (with safety of negatives replaced with 0)
	void crescereAlpha_s (int8_t alpha);

private:

	//Base sprite object
	Sprite *sprite;

	//Holds data on resolution and number of sprites in sheet
	int imagesX, imagesY, resX, resY;

};
