#include "stdafx.h"
#include "Rectangle.h"

namespace {

	float screenWidth, screenHeight;
	float cameraX, cameraY;

}

Rectangle::Rectangle () {

	this->x = 0.0f;
	this->y = 0.0f;
	this->width = 0.0f;
	this->height = 0.0f;

}

Rectangle::Rectangle (float x, float y, float width, float height) {

	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

}

Rectangle::~Rectangle () {



}

bool Rectangle::rectOnScreen () {

	return ((this->x + this->width >= cameraX) && (this->y + this->height >= -cameraY) && (this->x <= cameraX + 1.33333333f) && (this->y <= 1.0f - cameraY));

}

void Rectangle::updateScreenDimentions (float width, float height) {

	screenWidth = width;
	screenHeight = height;

}

void Rectangle::renderRect (GPU_Target *screen, SDL_Color color) {

	GPU_Rectangle (screen, screenWidth * (this->x - cameraX), screenHeight * (this->y + cameraY), screenWidth * (this->x - cameraX + this->width), screenHeight * (this->y + cameraY + this->height), color);

}

bool Rectangle::rectIsColliding (Rectangle r1, Rectangle r2) {

	//Complicated but standard Rectangle collision algorithm
	if (r1.x <= r2.x + r2.width &&
		r1.x + r1.width >= r2.x &&
		r1.y <= r2.y + r2.height &&
		r1.height + r1.y >= r2.y) {

		return true;

	} else {

		return false;

	}

}

bool Rectangle::pointInRect (Rectangle rect, float x, float y) {

	//Complicated but standard Rectangle collision algorithm
	if (rect.x <= x &&
		rect.y <= y &&
		rect.width + rect.x >= x &&
		rect.height + rect.y >= y) {

		return true;

	} else {

		return false;

	}

}

void Rectangle::setCamera (float x, float y) {

	cameraX = x; 
	cameraY = y;

}

//Getters and setters

float Rectangle::getX () {

	return this->x;

}

float Rectangle::getY () {

	return this->y;

}

float Rectangle::getWidth () {

	return this->width;

}

float Rectangle::getHeight () {

	return this->height;

}

void Rectangle::setX (float x) {

	this->x = x;

}

void Rectangle::setY (float y) {

	this->y = y;

}

void Rectangle::setWidth (float width) {

	this->width = width;

}

void Rectangle::setHeight (float height) {

	this->height = height;

}

void Rectangle::setPos (float x, float y) {

	this->x = x;
	this->y = y;

}

void Rectangle::setSize (float width, float height) {

	this->width = width;
	this->height = height;

}

//Translation methods

void Rectangle::translate (float x, float y) {

	this->x += x; //Move
	this->y += y;

}

void Rectangle::scale (float width, float height) {

	this->width *= width; //Scales the width and height
	this->height *= height;

}

//Rotate hitbox 90* (flip width and height)
void Rectangle::flip () {

	float temp = this->width; //Temporary value because width value is about to be replaced

	this->width = this->height; //Replace width by height
	this->height = temp; //Replace height by previous width

}
