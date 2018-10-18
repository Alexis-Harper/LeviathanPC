#pragma once

#include "Rectangle.h"
#include "GameObject.h"
#include "Sprite.h"

class Arena {

public:

	Arena ();
	Arena (const char *filename);
	~Arena ();

	static void init ();

	void update ();
	void render (GPU_Target *screen);

	//Call on player move to move camera in appropriate way
	void playerMoveCamera (Rectangle playerHitbox, float x, float y);

	//See if player can move or not
	bool* canMove (Rectangle playerHitbox);

	void pause (int pause);

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

