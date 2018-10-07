#include "stdafx.h"
#include "Exit.h"

namespace {

	struct Exit::ExitList *first = NULL, *last = NULL;

}

Exit::Exit (std::string location, Rectangle box, float playerX, float playerY, float cameraOffsetX, float cameraOffsetY) {

	//Copy location string
	this->location = location;

	//Set hitbox of exit
	this->hitbox = box;

	//Set floats on player and camera stuff
	this->playerX = playerX;
	this->playerY = playerY;
	this->cameraOffsetX = cameraOffsetX;
	this->cameraOffsetY = cameraOffsetY;

}

Exit::~Exit () {



}

float Exit::getPlayerX () {

	return this->playerX;

}

float Exit::getPlayerY () {

	return this->playerY;

}

float Exit::getCamPosX () {

	return (this->playerX - this->cameraOffsetX - 0.5f);

}

float Exit::getCamPosY () {

	return (this->playerY - this->cameraOffsetY - 0.5f);

}

void Exit::createExitList (Exit *exit) {

	first = new Exit::ExitList (exit);

	last = first;

}

void Exit::addExitList (Exit *exit) {

	struct Exit::ExitList *prev = last;

	last = new Exit::ExitList (exit);

	prev->next = last;

}

void Exit::deleteExitList () {

	struct ExitList *e, *m;

	e = first;

	while (e) {

		delete e->exit;

		m = e->next;

		delete e;

		e = m;

	}

	first = NULL;
	last = NULL;

}

void Exit::testForExit (Arena **arena, Player *player, SDL_Renderer *renderer) {

	struct ExitList *exit = first;

	while (exit) {

		if (Rectangle::rectIsColliding (exit->exit->hitbox, player->getHixbox ())) {

			//Set player position
			player->setPosition (exit->exit->getPlayerX (), exit->exit->getPlayerY ());

			//Set camera position (with offset)
			Sprite::setCamera (exit->exit->getCamPosX (), exit->exit->getCamPosY ()); 

			//Get location string
			char *buf = new char[exit->exit->location.length () + 1];
			strcpy (buf, exit->exit->location.c_str ());

			//Replace arena
			delete *arena;
			*arena = new Arena (buf, renderer); 

			//Delete allocated buffer (prevent mem leak)
			delete[] buf;

			//Exit loop
			break;

		}

		exit = exit->next;

	}

}
