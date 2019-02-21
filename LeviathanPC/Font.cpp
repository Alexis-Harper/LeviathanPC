#include "stdafx.h"
#include "Font.h"

//Font constants
namespace GameFonts {

	const char *MAIN_FONT = "assets/typefaces/helvetica.ttf";

};

namespace {

	//Screen and camera dimentions
	float screenWidth, screenHeight;
	float cameraX, cameraY;

	/*
	* Global that measures the number of screen dimention changes over time so
	* that when there is a dimention change, if the object's number doesn't 
	* match, then it will know it needs to change the size and will change it
	*/
	Uint32 sizeChanges = 0;

};

Font::Font (const char *filename, Uint32 pointSize) {

	//Calculate size
	Uint32 point = (Uint32) (pointSize * screenHeight / 740);

	//Color
	this->color = NFont::Color (0, 0, 0, 255);

	//Load font
	this->font.load (filename, point);

	//Set filename
	this->filename = filename;

	//Keep size
	this->size = pointSize;
	this->changes = sizeChanges;

}

Font::Font (const char *filename, Uint32 pointSize, NFont::Color color) {

	//Calculate size
	Uint32 point = (Uint32) (pointSize * screenHeight / 740);

	//Color
	this->color = color;

	//Load font
	this->font.load (filename, point, color);

	//Set filename
	this->filename = filename;

	//Keep size
	this->size = pointSize;
	this->changes = sizeChanges;

}

Font::Font (const char *filename, Uint32 pointSize, int style) {

	//Calculate size
	Uint32 point = (Uint32) (pointSize * screenHeight / 740);

	//Style
	this->color = NFont::Color (0, 0, 0, 255);
	this->style = style;

	//Load font
	this->font.load (filename, point, this->color, style);

	//Set filename
	this->filename = filename;

	//Keep size
	this->size = pointSize;
	this->changes = sizeChanges;

}

Font::Font (const char *filename, Uint32 pointSize, NFont::Color color, int style) {

	//Calculate size
	Uint32 point = (Uint32) (pointSize * screenHeight / 740);

	//Style
	this->color = color;
	this->style = style;

	//Load font
	this->font.load (filename, point, color, style);

	//Set filename
	this->filename = filename;

	//Keep size
	this->size = pointSize;
	this->changes = sizeChanges;

}

Font::~Font () {

	//Free font
	this->font.free ();

}

void Font::updateScreenDimentions (float w, float h) {

	//Update dimentions
	screenWidth = w;
	screenHeight = h;

	//Add to size change counter on size change
	sizeChanges++;

}

void Font::setCamera (float x, float y) {

	//Update camera position
	cameraX = x;
	cameraY = y;

}

NFont* Font::getFont () {

	//If the object's count doesn't match the correct number, fix it
	if (this->changes != sizeChanges) {

		//Calculate size
		Uint32 point = (Uint32) (this->size * screenHeight / 740);

		//Free existing font
		this->font.free ();

		//Load _new font of different size but same typeface
		this->font.load (this->filename, point, this->color, this->style);

	}

	//Return pointer to object's font so that rendering can be done
	return &this->font;

}

float Font::getX_d (float x) {

	//Translate camera then scale to dimention
	return (x - cameraX) * screenWidth;

}

float Font::getY_d (float y) {

	//Translate camera then scale to dimention
	return (y + cameraY) * screenHeight;

}

float Font::getX_s (float x) {

	//Scale position to dimention
	return x * screenWidth;

}

float Font::getY_s (float y) {

	//Scale position to dimention
	return y * screenHeight;

}

NFont::Rectf Font::getRect_d (float x, float y, float width, float height) {

	float xPos = (x - cameraX) * screenWidth;
	float yPos = (y + cameraY) * screenHeight;
	float wDim = width * screenWidth;
	float hDim = height * screenHeight;

	return NFont::Rectf (xPos, yPos, wDim, hDim);

}

NFont::Rectf Font::getRect_s (float x, float y, float width, float height) {

	float xPos = x * screenWidth;
	float yPos = y * screenHeight;
	float wDim = width * screenWidth;
	float hDim = height * screenHeight;

	return NFont::Rectf (xPos, yPos, wDim, hDim);

}
