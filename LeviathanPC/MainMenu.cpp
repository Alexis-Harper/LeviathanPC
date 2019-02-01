#include "stdafx.h"
#include "MainMenu.h"

MainMenu::MainMenu (Font *font, SpriteSheet *buttons) {

	this->font = font;
	this->buttons = buttons;

}

MainMenu::~MainMenu () {



}

void MainMenu::update (GameState & gameState, int windowResX, int windowResY) {

	//X and Y ints
	int x, y;

	//Check mouse state
	bool isPressed = (SDL_GetMouseState (&x, &y) & SDL_BUTTON (SDL_BUTTON_LEFT));

	//Gets virtual mouse state
	float virtualX = (float) x / windowResX;
	float virtualY = (float) y / windowResY;

	//Update buttons
	if (this->menuButtons.playGame.update (virtualX, virtualY, isPressed) == true) {

		gameState = GameState::GAME;

	}

}

void MainMenu::render (GPU_Target *screen) {

	this->background.srender (screen, 0.0f, 0.0f, 1.0f, NULL);

	this->menuButtons.playGame.render (screen, this->buttons, this->font);

}
