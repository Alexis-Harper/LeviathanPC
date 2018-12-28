#pragma once

/**
 * Author:    Alexis Harper
 * Created:   15.09.2018
 *
 * Description: GameObject is an abstract class for all game entities,
 *              providing a base, allowing for polymorphism.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 **/

#include "Audio.h"

class GameObject {

public:

	GameObject ();
	~GameObject ();

	//This is good
	virtual bool update () = 0;
	virtual void render () = 0;

	bool damage (int damage);

	virtual void death () = 0;

	int getHp ();
	int getHpMax ();
	int getAttack ();
	int getSpeed ();

	void setHp (int hp);
	void setHpMax (int hpMax);
	void setAttack (int attack);
	void setSpeed (int speed);

private:

	//AI aspect
	struct AIState {

		void (GameObject::*currentAIAction) (AIState&);

		int state;

	};
	
	AIState objectAIState;

	//Attacks
	void (GameObject::*attackMele) ();
	void (GameObject::*ranged) ();

	//Stats
	int hp;
	int hpMax;
	int attack;
	int speed;

protected:

	virtual void loadSound () = 0;

	std::vector<Audio::Effect> soundEffects;

	//AI functions

	//Move functions

};

