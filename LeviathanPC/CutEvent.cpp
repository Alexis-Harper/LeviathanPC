#include "stdafx.h"
#include "CutEvent.h"

namespace {

	struct CutEvent::EventList *first = NULL, *last = NULL;

}

CutEvent::CutEvent (std::string cutscene, Rectangle hitbox) {

	//Set location of cutscene
	this->scene = cutscene;

	std::cout << this->scene << "\n";

	//Set hitbox of scene
	this->hitbox = hitbox;

}

CutEvent::~CutEvent () {



}

void CutEvent::createEventList (CutEvent *eventObject) {

	first = _new EventList (eventObject);

	last = first;

}

void CutEvent::addEventList (CutEvent *eventObject) {

	last->next = _new EventList (eventObject);

	last = last->next;

}

void CutEvent::deleteEventList () {

	struct EventList *e, *m;

	e = first;

	while (e) {

		delete e->cutEvent;

		m = e->next;

		delete e;

		e = m;

	}

	first = NULL;
	last = NULL;

}

void CutEvent::testForEvent (GameState *state, Arena **arena, Cutscene **scene, Player *player) {

	//Goes through linked list
	struct EventList *eventPtr = first;

	while (eventPtr) {

		//Check if player is in event area
		if (Rectangle::rectIsColliding (eventPtr->cutEvent->hitbox, player->getHitbox ())) {

			//Change game state
			*state = GameState::CUTSCENE;

			//Gets cutscene string
			char *buf = _new char[eventPtr->cutEvent->scene.length () + 1];
			strcpy (buf, eventPtr->cutEvent->scene.c_str ());

			//TODO: If cutscene doesn't exist, delete it (this may not be necessary after I finish cutscene code)
			if (*scene != NULL) {

				delete *scene;

			}

			//Loads up cutscene
			*scene = _new Cutscene (buf);

			//Clear event list now
			deleteEventList ();

			//Deletes allocated buffer 
			delete[] buf;

			//Clears arena music
			(*arena)->clearMusic ();

			//Deletes arena
			delete *arena;
			*arena = NULL;

			//Break from loop
			break;

		}
		
		//Go to next pointer
		eventPtr = eventPtr->next;

	}

}
