#pragma once


class Vector {

public:

	Vector ();
	Vector (int);
	~Vector ();

	static float dotProduct (Vector, Vector);
	static Vector crossProduct (Vector, Vector);

	static float magnitude (Vector);

	int getSize ();

	float getValue (int);

	std::vector<float> getVector ();

	void resize (int);

	void setValue (int, float);

	void setVector (std::vector<float>);

	Vector scalarMultiply (float);

private:

	std::vector<float> vect;

	int size;

};
