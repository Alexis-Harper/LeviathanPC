#include "stdafx.h"
#include "Player.h"

#include "Input.h"

Player::Player () {

	this->spritesheet = new SpriteSheet ((char*) "assets/sprites.bmp", 2, 2);

}

Player::~Player () {



}

void Player::eightDirection (bool *move) {

	this->canMove[0] = move[0];
	this->canMove[1] = move[1];
	this->canMove[2] = move[2];
	this->canMove[3] = move[3];

}

void Player::update (Arena *arena) {

	this->direction = (EightDirection) Input::eightDirection ();

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

	this->vx *= (float) (0.005f *  Input::getDelta());
	this->vy *= (float) (0.006f *  Input::getDelta());

	this->hitbox.translate ((float) (this->vx), (float) (this->vy));
	
	arena->playerMoveCamera (this->hitbox, vx, -vy);

}

void Player::render (GPU_Target *screen) {

	this->spritesheet->render (screen, this->hitbox.getX (), this->hitbox.getY (), 0.5f, 0, 0);

}

void Player::setPosition (float x, float y) {

	this->hitbox.setPos (x, y);

}

Rectangle Player::getHixbox () {

	return this->hitbox;

}
