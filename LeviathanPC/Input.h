#pragma once

namespace Input {

	void init ();
	void update ();

	bool keyHeld (int key);

	void setDelta (double delta);
	double getDelta ();

	void isControllerUsed (bool isUsed);

	void joyButtonPressed (int index, bool pressed);

	void joyAxis0X (float axis0XValue);
	void joyAxis0Y (float axis0YValue);
	void joyAxis1X (float axis1XValue);
	void joyAxis1Y (float axis1YValue);

	int eightDirection ();
	int facingDirection ();

};
