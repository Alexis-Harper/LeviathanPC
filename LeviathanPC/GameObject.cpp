#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject () {



}

GameObject::~GameObject () {



}

bool GameObject::damage (int attack) {

	if (attack >= this->hp) {

		this->death ();

		return true;

	} else {

		this->hp -= attack;

		return false;

	}

}

int GameObject::getHp () {

	return this->hp;

}

int GameObject::getHpMax () {

	return this->hpMax;

}

int GameObject::getAttack () {

	return this->attack;

}

int GameObject::getSpeed () {

	return this->speed;

}

void GameObject::setHp (int value) {

	this->hp = value;

}

void GameObject::setHpMax (int value) {

	this->hpMax = value;

}

void GameObject::setAttack (int value) {

	this->attack = value;

}

void GameObject::setSpeed (int value) {

	this->speed = value;

}
