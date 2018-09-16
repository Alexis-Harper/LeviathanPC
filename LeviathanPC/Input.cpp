#include "stdafx.h"
#include "Input.h"

namespace Input {

	namespace {

		double delta;
		
		const Uint8 *keyboard;

		int direction;

	}

	void update () {

		keyboard = SDL_GetKeyboardState (NULL);

		bool up = keyHeld (SDL_SCANCODE_UP);
		bool right = keyHeld (SDL_SCANCODE_RIGHT);
		bool down = keyHeld (SDL_SCANCODE_DOWN);
		bool left = keyHeld (SDL_SCANCODE_LEFT);

		if (up && !right && !down && !left) {

			direction = UP;

		} else if (up && right && !down && !left) {

			direction = UP_RIGHT;

		} else if (!up && right && !down && !left) {

			direction = RIGHT;

		} else if (!up && right && down && !left) {

			direction = DOWN_RIGHT;

		} else if (!up && !right && down && !left) {

			direction = DOWN;

		} else if (!up && !right && down && left) {

			direction = DOWN_LEFT;

		} else if (!up && !right && !down && left) {

			direction = LEFT;

		} else if (up && !right && !down && left) {

			direction = UP_LEFT;

		} else {

			direction = NONE;

		}

	}

	bool keyHeld (int index) {

		return keyboard[index];

	}

	void setDelta (double value) {

		delta = value;

	}

	double getDelta () {

		return delta;

	}

	int eightDirection () {

		return direction;

	}

};
