#pragma once

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

