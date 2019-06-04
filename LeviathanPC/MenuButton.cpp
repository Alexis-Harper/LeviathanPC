#include "stdafx.h"
#include "MenuButton.h"


namespace 
{
	bool pressedLastFrame = false;
}


MenuButton::MenuButton (const char *text, float x, float y) 
{
	this->displayedText = text;
	//this->font = font;

	this->hitbox.setPos (x, y);
}


MenuButton::~MenuButton ()
{

}


bool MenuButton::update (float x, float y, bool pressed)
{
	if (Rectangle::pointInRect (this->hitbox, x, y)) 
	{
		if (pressed && !pressedLastFrame)
		{
			//Tell it a button was pressed
			pressedLastFrame = true;

			//If button is pressed, return true
			return true;
		} 
		else 
		{
			//If hovered, set to selected mode
			this->selected = true;

			if (!pressed && pressedLastFrame) 
			{
				pressedLastFrame = false;
			}
		}
	} 
	else 
	{
		//If not hovered, set to not selected
		this->selected = false;
	}

	return false;
}


void MenuButton::render (GPU_Target *screen, SpriteSheet *buttonSheet, 
						 Font *font) 
{

	//Show button 
	buttonSheet->srender (screen, this->hitbox.getX (), this->hitbox.getY (),
						  1.0, 0, (this->selected == true ? 1 : 0));

	//Calculate rectangle to display text in
	NFont::Rectf textRect = Font::getRect_s (this->hitbox.getX (), 
											 this->hitbox.getY () + 0.02361111111f,
											 0.66666666666f, 0.04444444443f);

	//Display centered text
	font->getFont ()->drawBox (screen, textRect, NFont::AlignEnum::CENTER, 
							   this->displayedText);

	return;
}
