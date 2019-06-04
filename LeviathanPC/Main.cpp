#include "stdafx.h"

#include "Game.h"


int main (int argc, char *args[]) 
{
	Game::init ();
	Game game;
	return game.run (argc, args);
}
