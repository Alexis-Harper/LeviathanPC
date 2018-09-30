#pragma once

namespace Input {

	void update ();

	bool keyHeld (int);

	void setDelta (double);
	double getDelta ();

	void isControllerUsed (bool);

	void joyButtonPressed (int, bool);

	void joyAxis0X (float);
	void joyAxis0Y (float);
	void joyAxis1X (float);
	void joyAxis1Y (float);

	int eightDirection ();

};
