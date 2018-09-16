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
