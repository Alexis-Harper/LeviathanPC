#pragma once

/**
 * Author:    Alexis Harper
 * Created:   12.11.2018
 *
 * Description: CutTile is a class that works on the cutscene tiles, storing
 *              the image and renders the tile itself.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 **/

#include "Sprite.h"

class CutTile 
{
public:

	CutTile (char *filename, float scale);
	~CutTile ();

	//Timing struct
	struct Timing 
	{
		float fade_in;
		float stay_time;
		float fade_out;
	};

	//Get timing data
	float getFadeIn ();
	float getStayTime ();
	float getFadeOut ();

	//Set timing data
	void setFadeIn (float value);
	void setStayTime (float value);
	void setFadeOut (float value);

	//Render tile
	void render (GPU_Target *screen);
	//Set alpha of tile
	void setAlpha (Uint8 alpha);

private:

	//Tile sprite
	Sprite *sprite;

	//Scale of tile
	float scale;

	//Timing of object
	struct Timing timing;
};
