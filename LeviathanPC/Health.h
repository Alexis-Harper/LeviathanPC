#pragma once

#include "Sprite.h"
#include "Shaders.h"

class Health {

public:

	Health ();
	~Health ();

	void modPlayerHealth (int health, int maxHealth);

	void render (GPU_Target *screen);

private:

	Sprite sprite = Sprite ((char*) "assets/671-small.bmp");

	ShaderProgram program;

	int uhealth;
	float health = 1.0f;

};

