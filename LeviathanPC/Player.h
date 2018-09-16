#pragma once

#include "Rectangle.h"

class Player {

public:

	Player ();
	~Player ();

	void eightDirection (bool*);

	void update ();
	void render ();

	Rectangle getHixbox ();

private:

	EightDirection direction;

	float vx, vy;

	bool canMove[4] = { true, true, true, true };

	Rectangle hitbox;

};

