#include "stdafx.h"
#include "PauseMenu.h"

PauseMenu::PauseMenu () {

	this->font = new Font (GameFonts::MAIN_FONT, 32, NFont::Color (127, 127, 127, 255));

}

PauseMenu::~PauseMenu () {



}

void PauseMenu::render (GPU_Target *screen) {

	float x = this->font->getX_s (0.224f);
	float y = this->font->getY_s (0.728f);

	//this->font->getFont ()->draw (screen, x, y, NFont::CENTER, "%d\n%d");

}
