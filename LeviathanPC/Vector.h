#pragma once

class Vector {

public:

	//Constructors and destructors
	Vector ();
	Vector (int);
	Vector (const float*);
	Vector (std::vector<float>);
	~Vector ();

	//Operators
	Vector& operator = (const float *arr) { *this = Vector (arr); }
	Vector& operator = (const std::vector<float>& vect) { *this = Vector (vect); }

	Vector& operator += (const Vector& rhs) { *this = add (*this, rhs); return *this; } //Addition
	friend Vector operator + (Vector lhs, const Vector& rhs) { lhs += rhs; return lhs; }

	Vector& operator -= (const Vector& rhs) { *this = sub (*this, rhs); return *this; } //Subtraction
	friend Vector operator - (Vector lhs, const Vector& rhs) { lhs -= rhs; return lhs; }

	friend float operator * (const Vector& lhs, const Vector& rhs) { return dotProduct (lhs, rhs); } //Dot product

	Vector& operator *= (const Vector& rhs) { *this = crossProduct (*this, rhs); return *this; } //Cross product

	//Math
	static Vector add (Vector, Vector);
	static Vector sub (Vector, Vector);

	static float dotProduct (Vector, Vector);
	static Vector crossProduct (Vector, Vector);

	static float magnitude (Vector);

	Vector scalarMultiply (float);

	//Getters and setters
	int getSize ();

	float getValue (int);

	std::vector<float> getVector ();

	void resize (int);

	void setValue (int, float);

	void setVector (std::vector<float>);

private:

	std::vector<float> vect;

	int size;

};
