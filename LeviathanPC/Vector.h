#pragma once

class Vector {

public:
	
	//Constructors and destructors
	Vector ();
	Vector (int size);
	Vector (const float *array);
	Vector (std::vector<float> vector);
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
	static Vector add (Vector vector1, Vector vector2);
	static Vector sub (Vector vector1, Vector vector2);

	static float dotProduct (Vector vector1, Vector vector2);
	static Vector crossProduct (Vector vector1, Vector vector2);

	static float magnitude (Vector vector);

	Vector scalarMultiply (float scalar);

	//Getters and setters
	int getSize ();

	float getValue (int index);

	std::vector<float> getVector ();

	void resize (int size);

	void setValue (int index, float value);

	void setVector (std::vector<float> vector);

private:

	std::vector<float> vect;

	int size;

};
