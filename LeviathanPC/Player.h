#pragma once

/**
 * Author:    Alexis Harper
 * Created:   15.09.2018
 *
 * Description: The Player class contains data on the current player, as well
 *              as doing the rendering.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 **/

#include "Rectangle.h"
#include "Sprite.h"
#include "Health.h"
#include "Shaders.h"

class Arena;

class Player {

public:

	Player ();
	~Player ();

	void update (Arena *activeArena);
	void render (GPU_Target *screen);

	void damage (int damage, Health *healthHud);
	void heal (int heal, Health *healthHud);

	Uint16 getAmmo ();
	Uint16 getMaxAmmo ();

	void setPosition (float x, float y);

	Rectangle getHixbox ();

private:

	struct PlayerStats {

		int hp, hpMax;
		Uint16 ammo = 16, maxAmmo = 23;
		float damageBoost = 0.0f;

	} stats;

	EightDirection direction;

	float vx, vy;

	bool canMove[4] = { true, true, true, true };

	SpriteSheet *spritesheet;

	ShaderProgram program;

	int uboost;

	Rectangle hitbox = Rectangle (0.5f, 0.5f, 0.031f, 0.082f);

};
