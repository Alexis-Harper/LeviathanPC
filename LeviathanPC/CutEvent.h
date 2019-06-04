#pragma once

/**
 * Author:    Alexis Harper
 * Created:   12.11.2018
 *
 * Description: Cut Event deals with telling if the player is in an event area, 
 *              and if they are, close the arena to load up a cutscene.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 **/

#include "GameState.h"

#include "Cutscene.h"
#include "Player.h"
#include "Arena.h"

class CutEvent 
{
public:

	CutEvent (std::string cutscene, Rectangle hitbox);
	~CutEvent ();

	//Event linked list structure
	struct EventList 
	{
		CutEvent *cutEvent;
		EventList *next;

		EventList (CutEvent * cutEvent) : cutEvent (cutEvent) 
		{ this->next = NULL; };
	};

	//Linked list 
	static void createEventList (CutEvent *event);
	static void addEventList (CutEvent *event);
	static void deleteEventList ();

	//Tests if event should play
	static void testForEvent (GameState & gameStateEnum, Arena *& arena, 
							  Cutscene *& scene, Player & player);

private:

	//Hitbox to cue event if touched by player
	Rectangle hitbox;

	//String location for cutscene
	std::string scene;
};
