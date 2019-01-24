#include "stdafx.h"
#include "PauseMenu.h"

PauseMenu::PauseMenu () {

	

}

PauseMenu::~PauseMenu () {



}

void PauseMenu::render (GPU_Target *screen) {

	//Get real XY coords to real dimention
	float x = this->font.getX_s (0.224f);
	float y = this->font.getY_s (0.728f);

	//this->font.getFont ()->draw (screen, x, y, NFont::CENTER, "%d\n%d");

}
