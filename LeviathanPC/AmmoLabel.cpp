#include "stdafx.h"
#include "AmmoLabel.h"

AmmoLabel::AmmoLabel () {

	

}

AmmoLabel::~AmmoLabel () {

	

}

void AmmoLabel::render (GPU_Target *screen, Player &player) {

	//Get ammo values
	Uint16 ammo = player.getAmmo ();
	Uint16 maxAmmo = player.getMaxAmmo ();

	//Get real dimentions of virtual coords
	float x = Font::getX_s (0.224f);
	float y = Font::getY_s (0.728f);

	//Render centered text displaying ammo had vs used
	this->font.getFont ()->draw (screen, x, y, NFont::CENTER, "%d\n%d", ammo, maxAmmo);

}
