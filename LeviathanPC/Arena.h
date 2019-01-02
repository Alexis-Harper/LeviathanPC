#pragma once

/**
 * Author:    Alexis Harper
 * Created:   14.09.2018
 *
 * Description: The Arena class handles arena loading from file, including
 *              arena rendering, hitbox detection for the player and walls,
 *              and player controlled camera movement.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 **/

#include "Rectangle.h"
#include "GameObject.h"
#include "Sprite.h"

class GameObject;

class Arena {

public:

	Arena (const char *filename);
	~Arena ();

	static void init ();

	void update ();
	void render (GPU_Target *screen);

	void updateGameObjects (GameObject::AIArgs args);
	void renderGameObjects (GPU_Target *screen);

	//Call on player move to move camera in appropriate way
	void playerMoveCamera (Rectangle playerHitbox, float x, float y);

	//See if object can move or not
	void canMove (Rectangle playerHitbox, bool *moveArray);

	//Test if things are in walls
	bool rectInWalls (Rectangle hitbox);

	//Mussic
	void pause (int pause);
	void clearMusic ();

private:

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

