#include "stdafx.h"
#include "Player.h"

#include "Input.h"

Player::Player () {



}

Player::~Player () {



}

void Player::update () {

	this->direction = (EightDirection) Input::eightDirection ();



}

Rectangle Player::getHixbox () {

	return this->hitbox;

}
