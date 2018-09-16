#pragma once

class Rectangle {

public:

	Rectangle ();
	Rectangle (float, float, float, float);
	~Rectangle ();

	static bool rectIsColliding (Rectangle r1, Rectangle r2);

	bool rectOnScreen ();

	float getX ();
	float getY ();
	float getWidth ();
	float getHeight ();

	void setX (float);
	void setY (float);
	void setWidth (float);
	void setHeight (float);

	void setPos (float, float);
	void setSize (float, float);

	void translate (float, float);
	void scale (float, float);

	void flip ();

private:

	float x;
	float y;

	float width;
	float height;

};

