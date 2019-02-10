#pragma once

/**
 * Author:    Alexis Harper
 * Created:   28.1.2019
 *
 * Description: A class that does the calculations for a button in a 
 *	            menu.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 **/

#include "Sprite.h"
#include "Rectangle.h"
#include "Font.h"

class MenuButton {

public:

	MenuButton (const char *text, float x, float y);
	~MenuButton ();

	bool update (float x, float y, bool pressed);
	void render (GPU_Target *screen, SpriteSheet *buttonSheet, Font *font);

private:

	//Char to display
	const char *displayedText;

	//Mouse hitbox
	Rectangle hitbox = Rectangle (0.0f, 0.0f, 0.666666666f, 0.091666666f);

	//Is button is selected
	bool selected;

};

