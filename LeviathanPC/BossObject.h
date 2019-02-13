#pragma once

#include "GameObject.h"

class BossObject : public GameObject {

public:

	BossObject ();
	~BossObject ();

private:

	//Boss phase (affects AI)
	int phase;

};

