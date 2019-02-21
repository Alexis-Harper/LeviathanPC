#pragma once

#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>

//Include SDL
#include <SDL.h>

//Include GPU
#include <SDL_gpu.h>

//NFont_gpu
#include "NFont_gpu.h"

//Add memory map info in Debug mode
#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>  
#include <crtdbg.h> 

#define _new new(_NORMAL_BLOCK, __FILE__, __LINE__)

#else

#define _new new

#endif

//Include standard libraries
#include <math.h>

#include <vector>

#include <string>

//Things to include everywhere (math)
#include "Rectangle.h"

//Reciporicals of \sqrt{2}
#define SQRT_2 0.70710678118f
#define _SQRT_2 -0.70710678118f

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
