#include "stdafx.h"
#include "Health.h"

#include "Input.h"


Health::Health () 
{
	//Load program
	this->program = loadShaderProgram ("assets/shaders/hud/health.vert",
									   "assets/shaders/hud/health.frag");

	//Set uniforms
	this->uhealth = GPU_GetUniformLocation (this->program.program, "health");
	GPU_SetUniformf (this->uhealth, 1.0f);

	//Close program
	GPU_ActivateShaderProgram (0, NULL);
}


Health::~Health ()
{
	//Free memory
	freeShaderProgram (this->program);
}


void Health::modPlayerHealth (int health, int maxHealth)
{
	//Set health float
	this->health = (float) health / maxHealth;

	return;
}


void Health::render (GPU_Target *screen) 
{
	//Activate shader program
	GPU_ActivateShaderProgram (this->program.program, &this->program.block);

	//Set uniforms
	this->uhealth = GPU_GetUniformLocation (this->program.program, "health");
	GPU_SetUniformf (this->uhealth, this->health);

	//Render health bar staticly
	this->spriteBase.srender (screen, 0.1f, 0.67f, 0.6f, NULL);

	//Deactivate shader program
	GPU_ActivateShaderProgram (0, NULL);

	return;
}
