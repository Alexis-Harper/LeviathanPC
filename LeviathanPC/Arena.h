#pragma once

#include "Rectangle.h"

class Arena {

public:

	Arena ();
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

};

