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

//Forward declaration to prevent dependencies
class Arena;

class GameObject {

public:

	GameObject ();
	virtual ~GameObject ();

	//AI information
	struct AIArgs {

		Arena *activeArena; //Arena for pathfinding
		Player *player; //Player hitbox for targeting

		Health *healthBar; //Health bar (for attacking the player)

		AIArgs (Arena *arena, Player *player, Health *health) : activeArena (arena), player (player), healthBar (health) {};

	};

	//Virtuals to update & render
	virtual bool update (AIArgs args) = 0;
	virtual void render (GPU_Target *screen) = 0;

	//Damages game object
	bool damage (int damage);

	//Virtual called on death
	virtual void death () = 0;

	//Get stats
	int getHp ();
	int getHpMax ();
	int getAttack ();
	int getSpeed ();

	Rectangle* getHitbox ();

	//Set stats
	void setHp (int hp);
	void setHpMax (int hpMax);
	void setAttack (int attack);
	void setSpeed (int speed);

protected:

	//AI aspect
	struct AIState {

		void (GameObject::*currentAIAction) (AIState&, AIArgs); //AI function pointer

		unsigned short int state; //Int containing flag bits for various things

		float range; //Range before pathfinding becomes attack
		float timer = 0; //Timer for certain actions

	} objectAIState;

	//Executes the AI if on screen
	void executeAI (AIState &objectAIState, AIArgs args);

	//Update damage boost
	void updateDamageBoost ();

	//Activates default shader program (for rendering)
	void activateDefaultShaderProgram ();

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

	//Directional enum for direction facing
	EightDirection direction;

	//Velocities
	float vx, vy;

	//Bool array on if object can move in each direction
	bool canMove[4] = { true, true, true, true };

	//Virtual for loading sounds for object
	virtual void loadSound () = 0;

	//Array of sound effects object can play
	std::vector<Audio::Effect> soundEffects;

	//AI functions
	void aStar (AIState &objectAIState, AIArgs args);
	void bodyAttack (AIState &objectAIState, AIArgs args);

	//Attack functions (TODO)

private:

	//Converts an angle into a direction for the object (for use in AI)
	void angleToDirection (double angle);

	//Damage boost value
	float damageBoost = 0.0f;

	//Shader data
	ShaderProgram program;
	int uboost;

	//Object count
	static unsigned int objectCount;

};
