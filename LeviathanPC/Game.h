#pragma once

/**
 * Author:    Alexis Harper
 * Created:   03.06.2019
 *
 * Description: The Game class deals with the game loop and event handling.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 **/

#include "ErrorEnum.h"
#include "GameState.h"

#include <chrono>

#include "Input.h"
#include "Player.h"
#include "Arena.h"
#include "Audio.h"
#include "Exit.h"
#include "Health.h"
#include "Cutscene.h"
#include "CutEvent.h"
#include "AmmoLabel.h"
#include "PauseMenu.h"
#include "MainMenu.h"
#include "Stats.h"
#include "Font.h"
#include "Sprite.h"
#include "MainMenu.h"
#include "PauseMenu.h"
#include "Window.h"


struct Menus
{
	//Menu font
	Font font = Font (GameFonts::MAIN_FONT, 32,
					  NFont::Color (200, 200, 200, 250));

	//Menu buttons
	SpriteSheet buttons = SpriteSheet (
		(char*) "assets/menu/MainButtons.png", 1, 2);

	//Menu objects
	MainMenu mainMenu = MainMenu (&this->font, &this->buttons);
	PauseMenu pauseMenu = PauseMenu (&this->font, &this->buttons);
};


class Game
{
public:

	Game ();
	~Game ();

	static void init (); //Initialize SDL

	int run (int argc, char *args[]); //Run game

private:

	void processEvents (); //Process SDL events
	void processPause (); //Process pausing
	void update (); //Update physics
	void render (GPU_Target * screen); //Render game


	//All main game vars
	Window window;
	SDL_Joystick *gameController;
	SDL_Haptic *hapticFeedback;
	Statistics statObject;
	Arena *activeArena;
	Cutscene *currentCutscene;
	Player player;
	Health health;
	AmmoLabel ammoLabel;
	GameState gameState;
	float pauseButtonBuffer;
	bool exitBool;
	SDL_Event sdlEvent;
	Menus menus;
};
