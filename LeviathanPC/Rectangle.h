#pragma once

/**
 * Author:    Alexis Harper
 * Created:   15.09.2018
 *
 * Description: The Rectangle class holds rectangle data and detects collision
 *              between rectangles, used for in game collision detection.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 **/

class Rectangle 
{
public:

	Rectangle ();
	Rectangle (float x, float y, float w, float h);
	~Rectangle ();

	static bool rectIsColliding (Rectangle r1, Rectangle r2);
	static bool rectInCircle (Rectangle rect, float cx, float cy, float cradius);
	static bool pointInRect (Rectangle rect, float x, float y);

	static void setCamera (float cameraX, float cameraY);
	bool rectOnScreen ();

	static void updateScreenDimentions (float width, float height);
	void renderRect (GPU_Target *screen, SDL_Color color);

	float getX ();
	float getY ();
	float getWidth ();
	float getHeight ();

	void setX (float x);
	void setY (float y);
	void setWidth (float width);
	void setHeight (float height);

	void setPos (float x, float y);
	void setSize (float width, float height);

	void translate (float x, float y);
	void scale (float width, float height);

	void flip ();

private:

	float x;
	float y;

	float width;
	float height;
};
