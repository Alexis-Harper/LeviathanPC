#pragma once

#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>

//Include SDL
#include <SDL.h>

#include <vector>

//Reciporicals of \sqrt{2}
#define SQRT_2 (float) 0.70710678118
#define _SQRT_2 (float) -0.70710678118

//Eight directon enum
enum EightDirection {

	NONE,
	UP,
	UP_RIGHT,
	RIGHT,
	DOWN_RIGHT,
	DOWN,
	DOWN_LEFT,
	LEFT,
	UP_LEFT

};
