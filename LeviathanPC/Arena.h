#pragma once

#include "Rectangle.h"
#include "GameObject.h"
#include "Sprite.h"

class Arena {

public:

	Arena ();
	Arena (const char *filename, SDL_Renderer *renderer);
	~Arena ();

	void render (SDL_Renderer *renderer);

	bool* canMove (Rectangle playerHitbox);

private:

	//Visuals
	Sprite *backgroundImage;

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

	static void createWallList (Rectangle *wall, Walls **first, Walls **last);
	static void addWallList (Rectangle *wall, Walls **last);

	struct GameObjects {

		GameObject *object;
		struct GameObjects *next;

		GameObjects (GameObject *data) : object (data) { this->next = NULL; };

	};

	struct GameObjects *gameObject_first, *gameObject_last;

	static void createGameObjectsList (GameObject *gameObject, GameObjects **first, GameObjects **last);
	static void addGameObjectsList (GameObject *gameObject, GameObjects **last);

};

