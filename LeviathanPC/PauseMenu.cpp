#include "stdafx.h"
#include "PauseMenu.h"

PauseMenu::PauseMenu (Font *font, SpriteSheet *buttons) {

	this->font = font;
	this->buttons = buttons;

}

PauseMenu::~PauseMenu () {



}

void PauseMenu::update (GameState &gameState, MainMenu &mainMenu, Arena *activeArena, float windowResY, float windowOffsets) {

	//X and Y ints
	int x, y;

	//Check mouse state
	bool isPressed = (SDL_GetMouseState (&x, &y) & SDL_BUTTON (SDL_BUTTON_LEFT));

	//Gets virtual mouse state
	float virtualX = (x - windowOffsets) / windowResY;
	float virtualY = y / windowResY;

	//Update buttons
	if (this->menuButtons.continueGame.update (virtualX, virtualY, isPressed) == true) {

		gameState = GameState::GAME;

	}

	if (this->menuButtons.mainMenu.update (virtualX, virtualY, isPressed) == true) {

		gameState = GameState::HOME_MENU;

		mainMenu.pause (0);
		activeArena->pause (1);

	}

}

void PauseMenu::render (GPU_Target *screen) {

	this->background.srender (screen, 0.0f, 0.0f, 1.0f, NULL);

	this->menuButtons.continueGame.render (screen, this->buttons, this->font);
	this->menuButtons.mainMenu.render (screen, this->buttons, this->font);

}
