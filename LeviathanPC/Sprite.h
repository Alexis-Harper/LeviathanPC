#pragma once

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
	//Set color blend
	void setColor (Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);
	//Set alpha
	void setAlpha (Uint8 alpha);

	//Increment or decrement (crescere) alpha value
	void crescereAlpha (int8_t alpha);
	//Increment or decrement (crescere) alpha value (with safety of negatives replaced with 0)
	void crescereAlpha_s (int8_t alpha);

	float getWidth ();
	float getHeight ();

	int getPWidth ();
	int getPHeight ();

private:

	GPU_Image *texture;

	float width, height;
	int pWidth, pHeight;

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
	//Set color blend
	void setColor (Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);
	//Set alpha
	void setAlpha (Uint8 alpha);

	//Increment or decrement (crescere) alpha value
	void crescereAlpha (int8_t alpha);
	//Increment or decrement (crescere) alpha value (with safety of negatives replaced with 0)
	void crescereAlpha_s (int8_t alpha);

private:

	Sprite *sprite;

	int imagesX, imagesY, resX, resY;

};
