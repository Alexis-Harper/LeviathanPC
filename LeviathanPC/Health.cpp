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

	this->uhealth = GPU_GetUniformLocation (this->program.program, "health");
	GPU_SetUniformf (this->uhealth, this->health);

	this->spriteBase.srender (screen, 0.1f, 0.67f, 0.6f, NULL);

	GPU_ActivateShaderProgram (0, NULL);

}
