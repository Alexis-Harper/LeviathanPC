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
#include "Player.h"
#include "Health.h"

class Arena;

class GameObject {

public:

	GameObject ();
	~GameObject ();

	//AI
	struct AIArgs {

		Arena *activeArena; //Arena for pathfinding
		Player *player; //Player hitbox for targeting

		Health *healthBar; //Health bar (for attacking the player)

		AIArgs (Arena *arena, Player *player, Health *health) : activeArena (arena), player (player), healthBar (health) {};

	};

	//This is good
	virtual bool update (AIArgs args) = 0;
	virtual void render (GPU_Target *screen) = 0;

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

protected:

	//AI aspect
	struct AIState {

		void (GameObject::*currentAIAction) (AIState&, AIArgs); //AI function pointer

		unsigned short int state; //Int containing flag bits for various things

		float range; //Range of the ranged attack

	} objectAIState;

	void executeAI (AIState &objectAIState, AIArgs args);

	//Attacks
	void (GameObject::*attackMele) () = NULL;
	void (GameObject::*ranged) () = NULL;

	//Hitbox
	Rectangle *hitbox;

	//Stats
	int hp;
	int hpMax;
	int attack;
	int speed;

	EightDirection direction;

	float vx, vy;

	bool canMove[4] = { true, true, true, true };

	virtual void loadSound () = 0;

	std::vector<Audio::Effect> soundEffects;

	//AI functions
	void aStar (AIState &objectAIState, AIArgs args);
	void bodyAttack (AIState &objectAIState, AIArgs args);

	//Attack functions

};
