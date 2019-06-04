#pragma once

/**
 * Author:    Alexis Harper
 * Created:   20.12.2018
 *
 * Description: Font.h deals with automatic font loading, sizing, and virtual
 *              position to window position calulations.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 **/

namespace GameFonts 
{
	extern const char *MAIN_FONT;
};

class Font 
{
public:

	Font (const char *filename, Uint32 pointSize);
	Font (const char *filename, Uint32 pointSize, NFont::Color color);
	Font (const char *filename, Uint32 pointSize, int style);
	Font (const char *filename, Uint32 pointSize, NFont::Color color, int style);
	~Font ();

	//Call on window size change to correct movement
	static void updateScreenDimentions (float x, float y);
	//Set camera position
	static void setCamera (float x, float y);

	//Get raw font
	NFont* getFont ();

	//Get real X/Width from virtual coords (dynamic)
	static float getX_d (float x);
	//Get real Y/Height from virtual coords (dynamic)
	static float getY_d (float y);
	//Get real X/Width from virtual coords (static)
	static float getX_s (float x);
	//Get real Y/Height from virtual coords (static)
	static float getY_s (float y);

	//Get real rectangle from virtual numbers (dynamic)
	static NFont::Rectf getRect_d (float x, float y, float width, float height);
	//Get real rectangle from virtual numbers (static)
	static NFont::Rectf getRect_s (float x, float y, float width, float height);

private:

	//NFont object
	NFont font;

	//Filename pointer for resizing
	const char *filename = NULL;

	//Holds size and change data
	Uint32 size, changes;

	//Style data
	NFont::Color color;
	int style = 0;
};
