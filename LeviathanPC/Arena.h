#pragma once

#include "Rectangle.h"
#include "GameObject.h"
#include "Sprite.h"

class Arena {

public:

	Arena ();
	Arena (const char *filename, SDL_Renderer *renderer);
	~Arena ();

	void update ();
	void render (SDL_Renderer *renderer);

	//Call on player move to move camera in appropriate way
	static void playerMoveCamera (float x, float y);

	//See if player can move or not
	bool* canMove (Rectangle playerHitbox);

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

	//Linked list pointers
	struct Walls *up_first, *up_last;
	struct Walls *right_first, *right_last;
	struct Walls *down_first, *down_last;
	struct Walls *left_first, *left_last;

	//Linked list build functions
	static void createWallList (Rectangle *wall, Walls **first, Walls **last);
	static void addWallList (Rectangle *wall, Walls **last);

	struct GameObjects {

		GameObject *object;
		struct GameObjects *next;

		GameObjects (GameObject *data) : object (data) { this->next = NULL; };

	};

	//Linked list pointer
	struct GameObjects *gameObject_first, *gameObject_last;

	//Linked list build functions
	static void createGameObjectsList (GameObject *gameObject, GameObjects **first, GameObjects **last);
	static void addGameObjectsList (GameObject *gameObject, GameObjects **last);

};

