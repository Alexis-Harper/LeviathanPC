#pragma once

/**
 * Author:    Alexis Harper
 * Created:   22.1.2019
 *
 * Description: A class that controls a pause menu.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 **/

#include "GameState.h"

#include "Font.h"
#include "Sprite.h"
#include "MenuButton.h"
#include "Arena.h"
#include "MainMenu.h"

class PauseMenu {

public:

	PauseMenu (Font *font, SpriteSheet *buttons);
	~PauseMenu ();

	//Update & render functions
	void update (GameState &gameState, MainMenu &mainMenu, Arena *activeArena, float windowResY, float windowOffset);
	void render (GPU_Target *screen);

private:

	//Background image
	Sprite background = Sprite ((char*) "assets/menu/pause/Background.png");

	//Pause object font data
	Font *font;

	//Pointer to button spritesheet
	SpriteSheet *buttons;

	//Buttons
	struct Buttons {

		MenuButton continueGame = MenuButton ("Continue Game", 0.33333333333f, 0.35f);
		MenuButton mainMenu = MenuButton ("Main Menu", 0.33333333333f, 0.5f);

	} menuButtons;

};
