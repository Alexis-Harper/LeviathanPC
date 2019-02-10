#pragma once

/**
 * Author:    Alexis Harper
 * Created:   28.1.2019
 *
 * Description: A class that controls the main menu.
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
#include "Audio.h"

class MainMenu {

public:

	MainMenu (Font *font, SpriteSheet *buttons);
	~MainMenu ();

	//Update & render functions
	void update (GameState &gameState, Arena *activeArena, float windowResY, float windowOffset);
	void render (GPU_Target *screen);

	//Music
	void pause (int pause);

private:

	//Music
	Audio::Music music = Audio::Music ("assets/Ambient_Hell.wav");

	//Background image
	Sprite background = Sprite ((char*) "assets/menu/main/Background.png");

	//Pause object font data
	Font *font;

	//Pointer to button spritesheet
	SpriteSheet *buttons;

	//Buttons
	struct Buttons {

		MenuButton playGame = MenuButton ("Play Game", 0.33333333333f, 0.5f);

	} menuButtons;

};

