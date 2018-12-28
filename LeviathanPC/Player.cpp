#include "stdafx.h"
#include "Player.h"

#include "Input.h"

Player::Player () {

	this->spritesheet = new SpriteSheet ((char*) "assets/Player_0.png", 1, 1);

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

void Player::eightDirection (bool *move) {

	this->canMove[0] = move[0];
	this->canMove[1] = move[1];
	this->canMove[2] = move[2];
	this->canMove[3] = move[3];

}

void Player::update (Arena *arena) {

	//Get direction
	this->direction = (EightDirection) Input::eightDirection ();

	//Get player velocity
	switch (this->direction) {

	case UP:
		this->vx = 0.0f;
		this->vy = -1.0f * canMove[0];
		break;

	case UP_RIGHT:
		this->vx = SQRT_2 * canMove[1];
		this->vy = _SQRT_2 * canMove[0];
		break;

	case RIGHT:
		this->vx = 1.0f * canMove[1];
		this->vy = 0.0f;
		break;

	case DOWN_RIGHT:
		this->vx = SQRT_2 * canMove[1];
		this->vy = SQRT_2 * canMove[2];
		break;

	case DOWN:
		this->vx = 0.0f;
		this->vy = 1.0f * canMove[2];
		break;

	case DOWN_LEFT:
		this->vx = _SQRT_2 * canMove[3];
		this->vy = SQRT_2 * canMove[2];
		break;

	case LEFT:
		this->vx = -1.0f * canMove[3];
		this->vy = 0.0f;
		break;

	case UP_LEFT:
		this->vx = _SQRT_2 * canMove[3];
		this->vy = _SQRT_2 * canMove[0];
		break;

	default:
		this->vx = 0.0f;
		this->vy = 0.0f;
		break;

	}

	//Adjust based of of delta time
	this->vx *= (float) (0.005f *  Input::getDelta());
	this->vy *= (float) (0.006f *  Input::getDelta());

	//Move player
	this->hitbox.translate ((float) (this->vx), (float) (this->vy));
	
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

}

void Player::render (GPU_Target *screen) {

	GPU_ActivateShaderProgram (this->program.program, &this->program.block);

	this->spritesheet->render (screen, this->hitbox.getX (), this->hitbox.getY (), 2.0f, 0, 0);

	this->uboost = GPU_GetUniformLocation (this->program.program, "damageBoost");
	GPU_SetUniformf (this->uboost, this->stats.damageBoost);

	GPU_ActivateShaderProgram (0, NULL);

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

Rectangle Player::getHixbox () {

	return this->hitbox;

}
