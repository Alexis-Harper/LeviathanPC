#pragma once

class Rectangle {

public:

	Rectangle ();
	Rectangle (float x, float y, float w, float h);
	~Rectangle ();

	static bool rectIsColliding (Rectangle r1, Rectangle r2);

	bool rectOnScreen ();

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

