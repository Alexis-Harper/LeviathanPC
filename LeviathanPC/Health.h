#pragma once

/**
 * Author:    Alexis Harper
 * Created:   19.10.2018
 *
 * Description: The Health class manages the HUD healthbar display.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 **/

#include "Sprite.h"
#include "Shaders.h"

class Health {

public:

	Health ();
	~Health ();

	void modPlayerHealth (int health, int maxHealth);

	void render (GPU_Target *screen);

private:

	Sprite spriteBase = Sprite ((char*) "assets/hud/health_base.bmp");

	ShaderProgram program;

	int uhealth;
	float health = 1.0f;

};

