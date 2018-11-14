#pragma once

#include "GameState.h"

#include "Cutscene.h"
#include "Player.h"
#include "Arena.h"

class CutEvent {

public:

	CutEvent (std::string cutscene, Rectangle hitbox);
	~CutEvent ();

	struct EventList {

		CutEvent *cutEvent;
		EventList *next;

		EventList (CutEvent *cutEvent) : cutEvent (cutEvent) { this->next = NULL; };

	};

	static void createEventList (CutEvent *event);
	static void addEventList (CutEvent *event);
	static void deleteEventList ();

	static void testForEvent (GameState *gameStateEnum, Arena **arena, Cutscene **scene, Player *player);

private:

	Rectangle hitbox;

	std::string scene;

};

