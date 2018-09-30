#include "stdafx.h"
#include "Input.h"

#include "ControllerDefines.h"

namespace Input {

	namespace {

		double delta;
		
		const Uint8 *keyboard;

		int direction;

		bool controller = false;

		bool joyButton[14] = { false };

		float joy0X, joy0Y, joy1X, joy1Y;

	}

	void update () {

		if (controller) {

			//Get angle
			double angle = atan2 (-joy0Y, joy0X);

			//Correct angle if neccessary
			if (joy0X == 0 && joy0Y == 0) {

				angle = 0;

			}

			bool up = joyButton[SDL_CONTROLLER_DUP];
			bool right = joyButton[SDL_CONTROLLER_DRIGHT];
			bool down = joyButton[SDL_CONTROLLER_DDOWN];
			bool left = joyButton[SDL_CONTROLLER_DLEFT];

			//Set direction to values
			if (((joy0X * joy0X) + (joy0Y * joy0Y) <= M_PI / 16) && !up && !right && !down && !left) {

				direction = NONE;

			} else if ((angle <= (5 * M_PI / 8) && angle >= (3 * M_PI / 8)) || (up && !right && !down && !left)) {

				direction = UP;

			} else if ((angle <= (3 * M_PI / 8) && angle >= (M_PI / 8)) || (up && right && !down && !left)) {

				direction = UP_RIGHT;

			} else if ((angle <= (M_PI / 8) && angle >= (-M_PI / 8)) || (!up && right && !down && !left)) {

				direction = RIGHT;

			} else if ((angle <= (-M_PI / 8) && angle >= (-3 * M_PI / 8)) || (!up && right && down && !left)) {

				direction = DOWN_RIGHT;

			} else if ((angle <= (-3 * M_PI / 8) && angle >= (-5 * M_PI / 8)) || (!up && !right && down && !left)) {

				direction = DOWN;

			} else if ((angle <= (-5 * M_PI / 8) && angle >= (-7 * M_PI / 8)) || (!up && !right && down && left)) {

				direction = DOWN_LEFT;

			} else if ((angle <= (-7 * M_PI / 8) || angle >= (7 * M_PI / 8)) || (!up && !right && !down && left)) {

				direction = LEFT;

			} else if ((angle <= (7 * M_PI / 8) && angle >= (5 * M_PI / 8)) || (up && !right && !down && left)) {

				direction = UP_LEFT;

			} else {

				direction = NONE;

			}

		} else {

			//Get keybord state
			keyboard = SDL_GetKeyboardState (NULL);

			//Get keys
			bool up = keyHeld (SDL_SCANCODE_W);
			bool right = keyHeld (SDL_SCANCODE_D);
			bool down = keyHeld (SDL_SCANCODE_S);
			bool left = keyHeld (SDL_SCANCODE_A);

			//Check direction and set it
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

	void isControllerUsed (bool isUsed) {

		controller = isUsed;

	}

	void joyButtonPressed (int index, bool value) {

		joyButton[index] = value;

	}

	void joyAxis0X (float value) {

		joy0X = value;

		//std::cout << "Joystick 0X: " << value << "\n";

	}

	void joyAxis0Y (float value) {

		joy0Y = value;

		//std::cout << "Joystick 0Y: " << value << "\n";

	}

	void joyAxis1X (float value) {

		joy1X = value;

		//std::cout << "Joystick 1X: " << value << "\n";

	}

	void joyAxis1Y (float value) {

		joy1Y = value;

		//std::cout << "Joystick 1Y: " << value << "\n";

	}

	int eightDirection () {

		return direction;

	}

};
