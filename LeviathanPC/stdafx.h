#pragma once

#include <iostream>

//Include SDL
#include <SDL.h>

#include <vector>
#include <map>

#define ERROR_SDL_INIT_VIDEO 2
#define ERROR_SDL_INIT_AUDIO 3
#define ERROR_SDL_WINDOW_FAILED_TO_LOAD 4
#define ERROR_SDL_AUDIO_WAV_LOAD 5

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
