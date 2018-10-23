#include "stdafx.h"
#include "Health.h"

#include "Input.h"

Health::Health () {

	this->program = loadShaderProgram ("assets/shaders/hud/health.vert", "assets/shaders/hud/health.frag");

	this->uhealth = GPU_GetUniformLocation (this->program.program, "health");
	GPU_SetUniformf (this->uhealth, 1.0f);

	GPU_ActivateShaderProgram (0, NULL);

}

Health::~Health () {

	freeShaderProgram (this->program);

}

void Health::modPlayerHealth (int health, int maxHealth) {

	this->health = (float) health / maxHealth;

}

void Health::render (GPU_Target *screen) {

	GPU_ActivateShaderProgram (this->program.program, &this->program.block);

	#ifdef _DEBUG

	if (Input::keyHeld (SDL_SCANCODE_T)) {

		this->health -= 0.02f;

	} else if (Input::keyHeld (SDL_SCANCODE_Y)) {

		this->health += 0.02f;

	}

	#endif

	this->uhealth = GPU_GetUniformLocation (this->program.program, "health");
	GPU_SetUniformf (this->uhealth, this->health);

	this->sprite.srender (screen, 0.2f, 0.75f, 1.0f, NULL);

	GPU_ActivateShaderProgram (0, NULL);

}
