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

	//Update/render player
	void update (Arena *activeArena);
	void render (GPU_Target *screen);

	//Damage/heal player (
	void damage (int damage, Health *healthHud);
	void heal (int heal, Health *healthHud);

	//Ammo getters
	Uint16 getAmmo ();
	Uint16 getMaxAmmo ();

	//Set position (used for _new arenas)
	void setPosition (float x, float y);

	//Get player hitbox
	Rectangle getHitbox ();

private:

	//Stat struct
	struct PlayerStats {

		int hp, hpMax;
		Uint16 ammo = 16, maxAmmo = 23;

		float damageBoost = 0.0f;
		float sprintCounter = 0.0f;

	} stats;

	//Player facing direction
	EightDirection direction;

	//Player velocity
	float vx, vy;

	//Holds data on what direction player can move in (from arena walls)
	bool canMove[4] = { true, true, true, true };

	//Sprite information
	SpriteSheet *spritesheet;
	Uint8 spriteDirection = 2; //Direction player is facing

	//Shader data
	ShaderProgram program;
	int uboost;
	int usprint;

	//Player hitbox
	Rectangle hitbox = Rectangle (0.5f, 0.5f, 0.031f, 0.082f);

};
