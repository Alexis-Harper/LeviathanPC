#pragma once

#include "Rectangle.h"
#include "Sprite.h"

class Player {

public:

	Player (SDL_Renderer*);
	~Player ();

	void eightDirection (bool*);

	void update ();
	void render (SDL_Renderer*);

	Rectangle getHixbox ();

private:

	EightDirection direction;

	float vx, vy;

	bool canMove[4] = { true, true, true, true };

	SpriteSheet *spritesheet;

	Rectangle hitbox = Rectangle (0.5f, 0.5f, 0.1f, 0.1f);

};

