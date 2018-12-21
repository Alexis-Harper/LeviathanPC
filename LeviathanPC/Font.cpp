#include "stdafx.h"
#include "Font.h"

namespace {

	float screenWidth, screenHeight;
	float cameraX, cameraY;

	Uint32 sizeChanges = 0;

};

Font::Font () {

	//Default constructor

}

Font::Font (const char *filename, Uint32 pointSize) {

	//Calculate size
	Uint32 point = pointSize * screenHeight / 740;

	//Load font
	this->font.load (filename, point);

	//Copy filename string
	if (this->filename != NULL) {

		delete[] this->filename;

	}

	this->filename = new char[strlen (filename) + 1];
	strcpy (this->filename, filename);

	//Keep size
	this->size = pointSize;
	this->changes = sizeChanges;

}

Font::Font (const char *filename, Uint32 pointSize, NFont::Color color) {

	//Calculate size
	Uint32 point = pointSize * screenHeight / 740;

	//Load font
	this->font.load (filename, point, color);

	//Copy filename string
	if (this->filename != NULL) {

		delete[] this->filename;

	}

	this->filename = new char[strlen (filename) + 1];
	strcpy (this->filename, filename);

	//Keep size
	this->size = pointSize;
	this->changes = sizeChanges;

}

Font::~Font () {

	if (this->filename != NULL) {

		delete[] this->filename;

	}

	this->font.free ();

}

void Font::updateScreenDimentions (float w, float h) {

	screenWidth = w;
	screenHeight = h;

	sizeChanges++;

}

void Font::setCamera (float x, float y) {

	cameraX = x;
	cameraY = y;

}

NFont* Font::getFont () {

	if (this->changes != sizeChanges) {

		//Calculate size
		Uint32 point = this->size * screenHeight / 740;

		//Load font
		this->font.free ();
		this->font.load (this->filename, point);

	}

	return &this->font;

}

float Font::getX_d (float x) {

	return (x - cameraX) * screenWidth;

}

float Font::getY_d (float y) {

	return (y + cameraY) * screenHeight;

}

float Font::getX_s (float x) {

	return x * screenWidth;

}

float Font::getY_s (float y) {

	return y * screenHeight;

}
