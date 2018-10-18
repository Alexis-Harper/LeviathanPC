#pragma once

#include "Rectangle.h"
#include "Arena.h"
#include "Player.h"

//Exit object
class Exit {

public:

	Exit (std::string location, Rectangle box, float playerX, float playerY, float cameraOffsetX, float cameraOffsetY);
	~Exit ();

	//Linked list for exits
	struct ExitList {

		Exit *exit;
		ExitList *next;

		ExitList (Exit *exit) : exit (exit) { next = NULL; };

	};

	float getPlayerX ();
	float getPlayerY ();
	float getCamPosX ();
	float getCamPosY ();

	static void createExitList (Exit *exit);
	static void addExitList (Exit *exit);
	static void deleteExitList ();

	static void testForExit (Arena **arena, Player *player);

private:

	Rectangle hitbox;

	std::string location;

	float playerX, playerY, cameraOffsetX, cameraOffsetY;

};

