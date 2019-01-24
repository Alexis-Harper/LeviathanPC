#include "stdafx.h"
#include "Player.h"

#include "ControllerDefines.h"

#include "Input.h"
#include "Arena.h"

Player::Player () {

	this->spritesheet = new SpriteSheet ((char*) "assets/player/Player.png", 4, 8);

	this->program = loadShaderProgram ("assets/shaders/player/player_db.vert", "assets/shaders/player/player_db.frag");

	this->uboost = GPU_GetUniformLocation (this->program.program, "damageBoost");
	GPU_SetUniformf (this->uboost, 0.0f);

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

	arena->canMove (this->hitbox, this->canMove); //Get if player can wall

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

	//Move player
	this->hitbox.translate (this->vx, this->vy);
	
	arena->playerMoveCamera (this->hitbox, vx, -vy);

	//If player is damage boosting, check timer
	if (this->stats.damageBoost > 0) {

		if (this->stats.damageBoost > Input::getDelta ()) {

			//If player has more boost than delta, then remove boost time
			this->stats.damageBoost -= (float) Input::getDelta ();

		} else {

			//If time is up, stop counter and allow damage
			this->stats.damageBoost = 0.0f;

		}
	
	}

	//std::cout << "Player: " << this->hitbox.getX () << ", " << this->hitbox.getY () << "\n";

}

void Player::render (GPU_Target *screen) {

	//Render player model
	GPU_ActivateShaderProgram (this->program.program, &this->program.block);

	//Player walking animation
	Uint8 animation = 0;

	if (this->vx != 0 || this->vy != 0) {

		animation = (int) (SDL_GetTicks () * 0.012) % 8;

	}

	//Damage boost shader uniform
	this->uboost = GPU_GetUniformLocation (this->program.program, "damageBoost");
	GPU_SetUniformf (this->uboost, this->stats.damageBoost);

	//Render
	this->spritesheet->render (screen, this->hitbox.getX () - 0.029f, this->hitbox.getY () - 0.003f, 2.0f, this->spriteDirection, animation);

	//Deactivate shader program
	GPU_ActivateShaderProgram (0, NULL);

	//Render hitbox if in debug mode
	#ifdef _DEBUG
	
	SDL_Color hitboxColor;

	hitboxColor.r = 20;
	hitboxColor.g = 255;
	hitboxColor.b = 20;
	hitboxColor.a = 200;

	this->hitbox.renderRect (screen, hitboxColor);

	#endif

}

void Player::damage (int damage, Health *healthHud) {

	if (this->stats.damageBoost > 0.0f) {

		return;

	} else {

		this->stats.damageBoost = 60.0f;

		if (damage >= this->stats.hp) {

			this->stats.hp = 0;

			//TEMP heals player instead of killing them
			this->stats.hp = this->stats.hpMax;

			healthHud->modPlayerHealth (this->stats.hp, this->stats.hpMax);

			//TODO Kill player

			return;

		} else {

			this->stats.hp -= damage;

			healthHud->modPlayerHealth (this->stats.hp, this->stats.hpMax);

			Input::rumble (0.5f, 100);

		}

	}

}

void Player::heal (int heal, Health *healthHud) {

	if (this->stats.hp + heal >= this->stats.hpMax) {

		this->stats.hp = this->stats.hpMax;

	} else {

		this->stats.hp += heal;

	}

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
