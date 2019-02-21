#pragma once

/**
 * Author:    Alexis Harper
 * Created:   30.12.2018
 *
 * Description: KillerShadow is a class that represents the Killer Shadow enemy.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 **/

#include "GameObject.h"

class KillerShadow : public GameObject {

public:

	KillerShadow (float x, float y);
	~KillerShadow ();

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

