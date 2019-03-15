#include "stdafx.h"
#include "Player.h"

#include "ControllerDefines.h"

#include "Input.h"
#include "Arena.h"

#ifdef _DEBUG

//Bools for hitboxes
namespace {

	

}

#endif

Player::Player () {

	this->spritesheet = _new SpriteSheet ((char*) "assets/player/Player.png", 4, 8);

	this->program = loadShaderProgram ("assets/shaders/player/player_db.vert", "assets/shaders/player/player_db.frag");

	this->uboost = GPU_GetUniformLocation (this->program.program, "damageBoost");
	GPU_SetUniformf (this->uboost, 0.0f);

	this->usprint = GPU_GetUniformLocation (this->program.program, "sprintCounter");
	GPU_SetUniformf (this->usprint, 0.0f);

	GPU_ActivateShaderProgram (0, NULL);

	this->stats.hp = 100;
	this->stats.hpMax = 100;

}

Player::~Player () {

	delete this->spritesheet;

	freeShaderProgram (this->program);

}

void Player::update (Arena *arena) {

	//Get direction
	this->direction = (EightDirection) Input::eightDirection ();

	//Get if player can wall
	arena->canMove (this->hitbox, this->canMove); 

	//Get player velocity
	switch (this->direction) {

	case UP:
		this->vx = 0.0f;
		this->vy = -1.0f * canMove[0];
		this->spriteDirection = 0;
		break;

	case UP_RIGHT:
		this->vx = SQRT_2 * canMove[1];
		this->vy = _SQRT_2 * canMove[0];
		this->spriteDirection = 0;
		break;

	case RIGHT:
		this->vx = 1.0f * canMove[1];
		this->vy = 0.0f;
		this->spriteDirection = 1;
		break;

	case DOWN_RIGHT:
		this->vx = SQRT_2 * canMove[1];
		this->vy = SQRT_2 * canMove[2];
		this->spriteDirection = 1;
		break;

	case DOWN:
		this->vx = 0.0f;
		this->vy = 1.0f * canMove[2];
		this->spriteDirection = 2;
		break;

	case DOWN_LEFT:
		this->vx = _SQRT_2 * canMove[3];
		this->vy = SQRT_2 * canMove[2];
		this->spriteDirection = 3;
		break;

	case LEFT:
		this->vx = -1.0f * canMove[3];
		this->vy = 0.0f;
		this->spriteDirection = 3;
		break;

	case UP_LEFT:
		this->vx = _SQRT_2 * canMove[3];
		this->vy = _SQRT_2 * canMove[0];
		this->spriteDirection = 0;
		break;

	default:
		this->vx = 0.0f;
		this->vy = 0.0f;
		break;

	}

	//Adjust based of of delta time
	this->vx *= (float) (0.005f *  Input::getDelta());
	this->vy *= (float) (0.005f *  Input::getDelta());

	//If run button is pressed, increase speed
	if (Input::keyHeld (SDL_SCANCODE_LALT) || Input::keyHeld (SDL_SCANCODE_RALT) || Input::buttonHeld (SDL_CONTROLLER_Y)) {

		this->vx *= 1.5f;
		this->vy *= 1.5f;

	}

	//Manage sprint counter
	if (this->stats.sprintCounter > 0.0f) {

		if (this->stats.sprintCounter > Input::getDelta ()) {

			//If player has more run time than delta, then remove boost time
			this->stats.sprintCounter -= (float) Input::getDelta ();

			if (this->stats.sprintCounter >= 25.0) {

				//Make player run faster (stacks with sprint)
				this->vx *= 1.5f;
				this->vy *= 1.5f;

			}

		} else {

			//If time is up, stop counter and allow damage
			this->stats.sprintCounter = 0.0f;

		}

	} else {

		//If damage boost is off, and key is held, dash sprint
		if (this->stats.damageBoost == 0.0f && Input::keyHeld (SDL_SCANCODE_SPACE)) {

			this->stats.sprintCounter = 60.0f;
			this->stats.damageBoost = 32.0f;

		}

	}

	//Move player
	this->hitbox.translate (this->vx, this->vy);
	
	arena->playerMoveCamera (this->hitbox, vx, -vy);

	//If player is damage boosting, check timer
	if (this->stats.damageBoost > 0.0f) {

		if (this->stats.damageBoost > Input::getDelta ()) {

			//If player has more boost than delta, then remove boost time
			this->stats.damageBoost -= (float) Input::getDelta ();

		} else {

			//If time is up, stop counter and allow damage
			this->stats.damageBoost = 0.0f;

		}
	
	}

	//If player is damage boosting, check timer
	if (this->stats.auraCounter > 0) {

		if (this->stats.auraCounter > Input::getDelta ()) {

			//If player has more boost than delta, then remove boost time
			this->stats.auraCounter -= (float) Input::getDelta ();

		} else {

			//If time is up, stop counter and allow damage
			this->stats.auraCounter = 0.0f;

		}

	} else {

		//If player presses button, 
		if (this->stats.damageBoost == 0.0f && this->stats.sprintCounter == 0.0f && Input::keyHeld (SDL_SCANCODE_RSHIFT)) {

			this->stats.auraCounter = 60.0f;

			float offX = this->hitbox.getX () - 0.01f; //(0.051 - 0.031) / 2.0
			float offY = this->hitbox.getY () - 0.01f; //(0.102 - 0.082) / 2.0

			Rectangle attackbox = Rectangle (offX, offY, 0.051f, 0.102f);

			//Deals good damage, plus
			int damage = this->stats.strength + this->stats.hpMax - this->stats.hp;

			arena->damageGameObjects (this->hitbox, damage, false);

		}

	}

	//Make it to where you can't just hold the button
	if (Input::keyHeld (SDL_SCANCODE_RSHIFT))
		this->stats.auraCounter = 60.0f;

	//std::cout << "Player: " << this->hitbox.getX () << ", " << this->hitbox.getY () << "\n";

}

void Player::render (GPU_Target *screen) {

	//Player walking animation
	Uint8 animation = 0;

	if (this->vx != 0 || this->vy != 0) {

		animation = (int) (SDL_GetTicks () * 0.012) % 8;

	}

	//Render player model
	GPU_ActivateShaderProgram (this->program.program, &this->program.block);

	//Damage boost shader uniform
	this->uboost = GPU_GetUniformLocation (this->program.program, "damageBoost");
	GPU_SetUniformf (this->uboost, this->stats.damageBoost);

	//Dash sprint boost counter uniform
	this->usprint = GPU_GetUniformLocation (this->program.program, "sprintCounter");
	GPU_SetUniformf (this->usprint, this->stats.sprintCounter);

	//Render
	this->spritesheet->render (screen, this->hitbox.getX () - 0.029f, this->hitbox.getY () - 0.003f, 2.0f, this->spriteDirection, animation);

	//Deactivate shader program
	GPU_ActivateShaderProgram (0, NULL);

	//Render hitbox if in debug mode
	#ifdef _DEBUG
	
	//Player Hitbox
	{
		SDL_Color hitboxColor;

		hitboxColor.r = 20;
		hitboxColor.g = 255;
		hitboxColor.b = 20;
		hitboxColor.a = 200;
		this->hitbox.renderRect (screen, hitboxColor);
	}

	//Player aura box
	{
		float offX = this->hitbox.getX () - 0.01f; //(0.051 - 0.031) / 2.0
		float offY = this->hitbox.getY () - 0.01f; //(0.102 - 0.082) / 2.0

		Rectangle attackbox = Rectangle (offX, offY, 0.051f, 0.102f);

		SDL_Color hitboxColor;

		hitboxColor.r = 20;
		hitboxColor.g = 20;
		hitboxColor.b = 255;
		hitboxColor.a = 200;

		attackbox.renderRect (screen, hitboxColor);
	}

	#endif

}

void Player::damage (int damage, Health *healthHud) {

	//If player is in damage boost, do nothing
	if (this->stats.damageBoost > 0.0f) {

		return;

	} else {

		//If it will kill player, do that, if not, damage them
		if (damage >= this->stats.hp) {

			this->stats.hp = 0;

			//TEMP heals player instead of killing them
			this->stats.hp = this->stats.hpMax;

			//Change health bar
			healthHud->modPlayerHealth (this->stats.hp, this->stats.hpMax);

			//TODO Kill player

			return;

		} else {

			//Set damage boost counter
			this->stats.damageBoost = 60.0f;

			//Reduce HP
			this->stats.hp -= damage;

			//Change health bar
			healthHud->modPlayerHealth (this->stats.hp, this->stats.hpMax);

			//Rumbe if controller is used
			Input::rumble (0.5f, 100);

			return;

		}

	}

}

void Player::heal (int heal, Health *healthHud) {

	//If healing more than health, set to max health, if not just heal
	if (this->stats.hp + heal >= this->stats.hpMax) {

		//Set to max health
		this->stats.hp = this->stats.hpMax;

	} else {

		//Heal
		this->stats.hp += heal;

	}

	//Change health bar
	healthHud->modPlayerHealth (this->stats.hp, this->stats.hpMax);

}

Uint16 Player::getAmmo () {

	return this->stats.ammo;

}

Uint16 Player::getMaxAmmo () {

	return this->stats.maxAmmo;

}

void Player::setPosition (float x, float y) {

	this->hitbox.setPos (x, y);

}

Rectangle Player::getHitbox () {

	return this->hitbox;

}
