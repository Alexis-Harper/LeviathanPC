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

namespace Input 
{
	// ******************************************
	// Init/update
	// ******************************************

	//Init input 
	void init ();

	//Update input
	void update ();

	// ******************************************
	// Getters
	// ******************************************

	//Gets if key/controller button is held
	bool keyHeld (int key);
	bool buttonHeld (int index);

	//Gets delta value (how many 1/60ths seconds in frame)
	double getDelta ();

	//Get if controller is used
	bool controllerUsed ();

	//Gets the eight direction data
	int eightDirection (); //Primary (walking) direction
	int facingDirection (); //Secondary (facing) direction

	// ******************************************
	// Setters
	// ******************************************

	//Set delta
	void setDelta (double delta);

	//Sets controller information
	void isControllerUsed (bool isUsed);
	void isHapticUsed (bool isUsed);

	//Set if joy button is pressed (for SDL event)
	void joyButtonPressed (int index, bool pressed);

	//Sets the joystick axis information (from SDL event)
	void joyAxis0X (float axis0XValue);
	void joyAxis0Y (float axis0YValue);
	void joyAxis1X (float axis1XValue);
	void joyAxis1Y (float axis1YValue);

	//Haptic feedback functions
	void setHapticFeedback (SDL_Haptic *haptic);
	
	// ******************************************
	//  Rumble
	// ******************************************

	//Rumbles
	void rumble (float strength, int duration);
};
