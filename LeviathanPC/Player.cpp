#include "stdafx.h"
#include "Player.h"

#include "Input.h"

Player::Player (SDL_Renderer *render) {

	this->sprite = new Sprite (render, (char*) "assets/temp.bmp");

}

Player::~Player () {



}

void Player::eightDirection (bool *move) {

	this->canMove[0] = move[0];
	this->canMove[1] = move[1];
	this->canMove[2] = move[2];
	this->canMove[3] = move[3];

}

void Player::update () {

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

	this->hitbox.translate (this->vx * 0.005f, this->vy * 0.005f);
	
}

void Player::render (SDL_Renderer *render) {

	this->sprite->render (render, this->hitbox.getX(), this->hitbox.getY(), 1.0f, NULL);

}

Rectangle Player::getHixbox () {

	return this->hitbox;

}
