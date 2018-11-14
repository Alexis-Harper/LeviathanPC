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

	first = new EventList (eventObject);

	last = first;

}

void CutEvent::addEventList (CutEvent *eventObject) {

	last->next = new EventList (eventObject);

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
		if (Rectangle::rectIsColliding (eventPtr->cutEvent->hitbox, player->getHixbox ())) {

			//Change game state
			*state = GameState::CUTSCENE;

			//Deletes arena
			delete *arena;

			//Gets cutscene string
			char *buf = new char[eventPtr->cutEvent->scene.length () + 1];
			strcpy (buf, eventPtr->cutEvent->scene.c_str ());

			//TODO: If cutscene doesn't exist, delete it (this may not be necessary after I finish cutscene code)
			if (*scene != NULL) {

				delete *scene;

			}

			//Loads up cutscene
			*scene = new Cutscene (buf);

			//Clear event list now
			deleteEventList ();

			//Deletes allocated buffer 
			delete[] buf;

			//Break from loop
			break;

		}
		
		//Go to next pointer
		eventPtr = eventPtr->next;

	}

}
