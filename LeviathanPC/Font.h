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

class Font {

public:

	Font ();
	Font (const char *filename, Uint32 pointSize);
	Font (const char *filename, Uint32 pointSize, NFont::Color color);
	~Font ();

	//Call on window size change to correct movement
	static void updateScreenDimentions (float x, float y);
	//Set camera position
	static void setCamera (float x, float y);

	NFont* getFont ();

	float getX_d (float x);
	float getY_d (float y);
	float getX_s (float x);
	float getY_s (float y);

private:

	NFont font;

	char *filename = NULL;
	Uint32 size, changes;

};

