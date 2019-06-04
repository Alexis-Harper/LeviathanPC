#include "stdafx.h"
#include "MainMenu.h"


MainMenu::MainMenu (Font *font, SpriteSheet *buttons) 
{
	this->font = font;
	this->buttons = buttons;

	this->music.pause (0);
}


MainMenu::~MainMenu () 
{

}


void MainMenu::update (GameState &gameState, Arena *activeArena, 
					   float windowResY, float windowOffset)
{
	//X and Y ints
	int x, y;

	//Check mouse state
	bool isPressed = (SDL_GetMouseState (&x, &y) & 
					  SDL_BUTTON (SDL_BUTTON_LEFT));

	//Gets virtual mouse state
	float virtualX = (x - windowOffset) / windowResY;
	float virtualY = y / windowResY;

	//std::cout << "(" << virtualX << ", " << virtualY << ")\n";

	//Update buttons
	if (this->menuButtons.playGame.update (virtualX, virtualY, isPressed) ==
		true) 
	{
		gameState = GameState::GAME;

		this->pause (1);
		activeArena->pause (0);
	}

	return;
}


void MainMenu::render (GPU_Target *screen) 
{
	this->background.srender (screen, 0.0f, 0.0f, 1.0f, NULL);

	this->menuButtons.playGame.render (screen, this->buttons, this->font);

	this->music.render ();

	return;
}


void MainMenu::pause (int pause) 
{
	this->music.pause (pause);

	return;
}
