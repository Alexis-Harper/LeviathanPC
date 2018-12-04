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

class CutTile {

public:

	CutTile (char *filename, float scale);
	~CutTile ();

	struct Timing {

		float fade_in;
		float stay_time;
		float fade_out;

	};

	float getFadeIn ();
	float getStayTime ();
	float getFadeOut ();

	void setFadeIn (float value);
	void setStayTime (float value);
	void setFadeOut (float value);

	void render (GPU_Target *screen);
	void setAlpha (Uint8 alpha);

private:

	Sprite *sprite;

	float scale;

	struct Timing timing;

};

