#include "stdafx.h"
#include "GameObject.h"

#include "Arena.h"

#define tstBit(flag, bit) (flag & (1 << bit))
#define setBit(flag, bit) flag = (flag | (1 << bit))
#define clrBit(flag, bit) flag = (flag & ~(1 << bit))

enum Flags {

	AI_STATE_FLAG_BODY_ATTACK

};

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

void GameObject::executeAI (AIState &objectAIState, AIArgs args) {

	//If the object is on screen, execute AI
	if (this->hitbox->rectOnScreen ()) {

		(this->*(this->objectAIState.currentAIAction)) (this->objectAIState, args);

	}

}

void GameObject::aStar (AIState &objectAIState, AIArgs args) {

	//Basic var declaration
	double angle = 0.0f;

	float xToPlayer = args.player->getHixbox ().getX () - this->hitbox->getX ();
	float yToPlayer = args.player->getHixbox ().getY () - this->hitbox->getY ();

	//Set test box rect
	Rectangle testBox;

	testBox.setX (this->hitbox->getX () + 0.25f);
	testBox.setY (this->hitbox->getY () + 0.25f);
	testBox.setWidth (0.5f);
	testBox.setHeight (0.5f);

	//If player is 
	if (args.activeArena->rectInWalls (testBox)) {

		//Set angle to angle to player
		angle = atan2 (-yToPlayer, xToPlayer);

	} else {

		//TODO Implement A* pathfinding algorithm to find new angle

	}

	//Set direction enum
	if ((angle <= (5 * M_PI / 8) && angle >= (3 * M_PI / 8))) {

		this->direction = UP;

	} else if ((angle <= (3 * M_PI / 8) && angle >= (M_PI / 8))) {

		this->direction = UP_RIGHT;

	} else if ((angle <= (M_PI / 8) && angle >= (-M_PI / 8))) {

		this->direction = RIGHT;

	} else if ((angle <= (-M_PI / 8) && angle >= (-3 * M_PI / 8))) {

		direction = DOWN_RIGHT;

	} else if ((angle <= (-3 * M_PI / 8) && angle >= (-5 * M_PI / 8))) {

		this->direction = DOWN;

	} else if ((angle <= (-5 * M_PI / 8) && angle >= (-7 * M_PI / 8))) {

		this->direction = DOWN_LEFT;

	} else if ((angle <= (-7 * M_PI / 8) || angle >= (7 * M_PI / 8))) {

		this->direction = LEFT;

	} else if ((angle <= (7 * M_PI / 8) && angle >= (5 * M_PI / 8))) {

		this->direction = UP_LEFT;

	} else {

		this->direction = NONE;

	}

	if ((sqrt (xToPlayer * xToPlayer + yToPlayer * yToPlayer) >= 0.2f) && (tstBit (objectAIState.state, AI_STATE_FLAG_BODY_ATTACK))) {

		objectAIState.currentAIAction = &GameObject::bodyAttack;

	}

}

void GameObject::bodyAttack (AIState &objectAIState, AIArgs args) {

	this->aStar (objectAIState, args);

	if (Rectangle::rectIsColliding (*this->hitbox, args.player->getHixbox ())) {

		args.player->damage (10, args.healthBar);

	}

}
