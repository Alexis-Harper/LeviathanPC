#pragma once

#include "Rectangle.h"
#include "Sprite.h"
#include "Arena.h"
#include "Health.h"
#include "Shaders.h"

class Player {

public:

	Player ();
	~Player ();

	void eightDirection (bool *boolArray);

	void update (Arena *activeArena);
	void render (GPU_Target *screen);

	void damage (int damage, Health *healthHud);
	void heal (int heal, Health *healthHud);

	void setPosition (float x, float y);

	Rectangle getHixbox ();

private:

	struct PlayerStats {

		int hp, hpMax;
		float damageBoost = 0.0f;

	} stats;

	EightDirection direction;

	float vx, vy;

	bool canMove[4] = { true, true, true, true };

	SpriteSheet *spritesheet;

	ShaderProgram program;

	int uboost;

	Rectangle hitbox = Rectangle (0.5f, 0.5f, 0.05f, 0.05f);

};

