#pragma once

/**
 * Author:    Alexis Harper
 * Created:   04.06.2019
 *
 * Description: TheDamned is a class that represents the The Damned enemy.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 **/

#include "GameObject.h"

class TheDamned : public GameObject
{
public:

	TheDamned (float x, float y);
	~TheDamned ();

	//Update and render implementations
	bool update (AIArgs args);
	void render (GPU_Target *screen);

	//Implimentation of death
	void death ();

private:

	//Loads sounds to play
	void loadSound ();

	//Spritesheet information
	SpriteSheet *spritesheet;
	Uint8 spriteDirection = 0;
};
