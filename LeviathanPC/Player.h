#pragma once

#include "Rectangle.h"
#include "Sprite.h"
#include "Arena.h"

class Player {

public:

	Player (SDL_Renderer*);
	~Player ();

	void eightDirection (bool *boolArray);

	void update (Arena *activeArena);
	void render (SDL_Renderer *renderer);

	void setPosition (float x, float y);

	Rectangle getHixbox ();

private:

	EightDirection direction;

	float vx, vy;

	bool canMove[4] = { true, true, true, true };

	SpriteSheet *spritesheet;

	Rectangle hitbox = Rectangle (0.5f, 0.5f, 0.05f, 0.05f);

};

