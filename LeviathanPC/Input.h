#pragma once

/**
 * Author:    Alexis Harper
 * Created:   14.09.2018
 *
 * Description: Input does advanced keyboard and controller input, as well as
 *              other things like the getter and setter for the delta value of
 *              each frame and functions for controlling haptic feedback.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 **/

namespace Input {

	void init ();
	void update ();

	bool keyHeld (int key);
	bool buttonHeld (int index);

	void setDelta (double delta);
	double getDelta ();

	bool controllerUsed ();

	void isControllerUsed (bool isUsed);
	void isHapticUsed (bool isUsed);

	void joyButtonPressed (int index, bool pressed);

	void joyAxis0X (float axis0XValue);
	void joyAxis0Y (float axis0YValue);
	void joyAxis1X (float axis1XValue);
	void joyAxis1Y (float axis1YValue);

	int eightDirection ();
	int facingDirection ();

	void setHapticFeedback (SDL_Haptic *haptic);
	void rumble (float strength, int duration);

};
