#pragma once

#include "Rectangle.h"
#include "GameObject.h"

class Arena {

public:

	Arena ();
	Arena (char*);
	~Arena ();

	bool* canMove (Rectangle);

private:

	//Wall linked lists
	struct Walls {

		Rectangle *rect;
		struct Walls *next;

		Walls (Rectangle *data) : rect (data) { this->next = NULL; };

	};

	struct Walls *up_first, *up_last;
	struct Walls *right_first, *right_last;
	struct Walls *down_first, *down_last;
	struct Walls *left_first, *left_last;

	static void createWallList (Rectangle*, Walls**, Walls**);
	static void addWallList (Rectangle*, Walls**);

	struct GameObjects {

		GameObject *object;
		struct GameObjects *next;

		GameObjects (GameObject *data) : object (data) { this->next = NULL; };

	};

	struct GameObjects *gameObject_first, *gameObject_last;

	static void createGameObjectsList (GameObject*, GameObjects**, GameObjects**);
	static void addGameObjectsList (GameObject*, GameObjects**);

};

