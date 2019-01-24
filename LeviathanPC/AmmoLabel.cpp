#include "stdafx.h"
#include "AmmoLabel.h"

AmmoLabel::AmmoLabel () {

	this->font = new Font (GameFonts::MAIN_FONT, 50, NFont::Color (200, 200, 200, 204), 1);

}

AmmoLabel::~AmmoLabel () {

	delete this->font;

}

void AmmoLabel::render (GPU_Target *screen, Player &player) {

	Uint16 ammo = player.getAmmo ();
	Uint16 maxAmmo = player.getMaxAmmo ();

	float x = this->font->getX_s (0.224f);
	float y = this->font->getY_s (0.728f);

	this->font->getFont ()->draw (screen, x, y, NFont::CENTER, "%d\n%d", ammo, maxAmmo);

}
