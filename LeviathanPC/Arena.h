#pragma once

/**
 * Author:    Alexis Harper
 * Created:   14.09.2018
 *
 * Description: The Arena class handles arena loading from file, including
 *              arena rendering, hitbox detection for the player and walls,
 *              and player controlled camera movement. There are two classes,
 *              one for regular arenas and one for special boss arenas. They
 *              both extend a base arena class.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 **/

#include "rapidjson/document.h"

#include "Rectangle.h"
#include "GameObject.h"
#include "Sprite.h"
#include "BossObject.h"

class GameObject;

//Calls correct arena based off of data in class
Arena* new_Arena (const char *filename);

class Arena {

public:

	//Arena base constructors and deconstructors
	Arena (rapidjson::Document &json);
	virtual ~Arena ();

	//Initiate Arena (before any constructors are called)
	static void init ();
	static void exit ();

	//Update and render methods
	virtual void update ();
	virtual void render (GPU_Target *screen);

	//Update/render all GameObjects in Arena
	virtual void updateGameObjects (GameObject::AIArgs args) = 0;
	virtual void renderGameObjects (GPU_Target *screen) = 0;

	//Check for damage for all GameObjects in Arena
	virtual bool damageGameObjects (Rectangle hitbox, int damage, bool destructable) = 0;
	virtual bool damageGameObjects (float cx, float cy, float cradius, int damage, bool destructable) = 0;

	//Call on player move to move camera in appropriate way
	void playerMoveCamera (Rectangle playerHitbox, float x, float y);

	//See if object can move or not
	void canMove (Rectangle playerHitbox, bool *moveArray);

	//Test if a rectangle is in a wall
	bool rectInWalls (Rectangle hitbox);

	//Music
	void pause (int pause);
	void clearMusic ();

protected:

	//Visuals
	Sprite *backgroundImage;
	float backgroundScale;

	//Wall linked lists
	struct Walls {

		Rectangle *rect;
		struct Walls *next;

		Walls (Rectangle *data) : rect (data) { this->next = NULL; };

	};

	//Linked list pointer (Movement Walls)
	struct Walls *up_first = NULL, *up_last = NULL;
	struct Walls *right_first = NULL, *right_last = NULL;
	struct Walls *down_first = NULL, *down_last = NULL;
	struct Walls *left_first = NULL, *left_last = NULL;

	//Linked list pointer (Camera Walls)
	struct Walls *choriz_first = NULL, *choriz_last = NULL;
	struct Walls *cvert_first = NULL, *cvert_last = NULL;

	//Linked list build functions
	static void createWallList (Rectangle *wall, Walls **first, Walls **last);
	static void addWallList (Rectangle *wall, Walls **last);

	//GameObject linked list
	struct GameObjects {

		GameObject *object;
		struct GameObjects *next;

		GameObjects (GameObject *data) : object (data) { this->next = NULL; };

	};

	//Linked list pointer
	struct GameObjects *gameObject_first = NULL, *gameObject_last = NULL;

	//Linked list build functions
	static void createGameObjectsList (GameObject *gameObject, GameObjects **first, GameObjects **last);
	static void addGameObjectsList (GameObject *gameObject, GameObjects **last);

};

class NormalArena : public Arena {

public:

	NormalArena (rapidjson::Document &json);
	~NormalArena ();

	//Update/render all GameObjects in Arena
	void updateGameObjects (GameObject::AIArgs args);
	void renderGameObjects (GPU_Target *screen);

	bool damageGameObjects (Rectangle hitbox, int damage, bool destructable);
	bool damageGameObjects (float cx, float cy, float cradius, int damage, bool destructable);

private:

	

};

class BossArena : public Arena {

public:

	BossArena (rapidjson::Document &json);
	~BossArena ();

	//Update/render all GameObjects in Arena
	void updateGameObjects (GameObject::AIArgs args);
	void renderGameObjects (GPU_Target *screen);

	bool damageGameObjects (Rectangle hitbox, int damage, bool destructable);
	bool damageGameObjects (float cx, float cy, float cradius, int damage, bool destructable);

private:

	//BossObject
	BossObject *boss;

};
