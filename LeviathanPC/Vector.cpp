#include "stdafx.h"
#include "Vector.h"

Vector::Vector () {

	this->size = 2; //Default size of 2D matrix (variable to speed things up)

	this->vect.resize (2); //Size

}

Vector::Vector (int num) {

	this->size = num; //Allow for a set width on creation (variable to speed things up)

	this->vect.resize (num); //Size

}

Vector::~Vector () {

	this->vect.clear ();

}

float Vector::dotProduct (Vector v1, Vector v2) {

	//Incompatable vectors return NULL
	if (v1.size != v2.size) {

		return NULL;

	}

	float sum = 0; //Initialize variable

	for (int i = 0; i < v1.size; i++) {

		sum += v1.vect[i] * v2.vect[i]; //Add multiplied variables together

	}

	return sum; //Return sum

}

Vector Vector::crossProduct (Vector v1, Vector v2) {

	//Incompatable vectors return NULL
	if (v1.size != 3 || v2.size != 3) {

		return NULL;

	}

	Vector returnVector (3); //Create 3D return vector

	returnVector.vect[0] = (v1.vect[1] * v2.vect[2]) - (v1.vect[2] * v2.vect[1]); //I'm not even going to explain
	returnVector.vect[1] = (v1.vect[2] * v2.vect[0]) - (v1.vect[0] * v2.vect[2]);
	returnVector.vect[2] = (v1.vect[0] * v2.vect[1]) - (v1.vect[1] * v2.vect[0]);

	return returnVector; //Return return vector

}

//Get magnitude, duh
float Vector::magnitude (Vector v) {

	float sum = 0; //Pythagorean theorum sum

	for (int i = 0; i < v.size; i++) {

		sum += pow (v.vect[i], 2); //Add square of all values (a^2 + b^2 + ...)

	}

	return sqrt (sum); //Pythagorean sqrt (c^2)

}

//Getters and setters

int Vector::getSize () {

	return this->size;

}

float Vector::getValue (int adress) {

	//Return NULL if the adress is invalid
	if (adress < this->size) {

		return vect[adress];

	} else {

		return NULL;

	}

}

std::vector<float> Vector::getVector () {

	return vect;

}

void Vector::resize (int num) {

	//Only resize if necessary
	if (this->size != num) {

		this->vect.resize (num);

	}

}

void Vector::setValue (int adress, float value) {

	//Don't try and change the value of a 
	if (adress < this->size) {

		this->vect[adress] = value;

	}

}

void Vector::setVector (std::vector<float> newVec) {

	//Resize if necessary
	if (newVec.size () != this->size) {

		size = (int) (newVec.size ());

		this->vect.resize (newVec.size ());

	}

	this->vect = newVec; //Replace vector

}

Vector Vector::scalarMultiply (float s) {

	Vector returnVector (this->size); //Create return vector of correct size

	for (int i = 0; i < this->size; i++) {

		returnVector.vect[i] = this->vect[i] * s; //Multiply all values by scalar

	}

	return returnVector; //Return return vector

}
