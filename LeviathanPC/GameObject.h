#pragma once

#include "Audio.h"

class GameObject {

public:

	GameObject ();
	~GameObject ();

	//This is good
	virtual bool update () = 0;
	virtual void render () = 0;

	bool damage (int);

	virtual void death () = 0;

	int getHp ();
	int getHpMax ();
	int getAttack ();
	int getSpeed ();

	void setHp (int);
	void setHpMax (int);
	void setAttack (int);
	void setSpeed (int);

private:

	//Stats
	int hp;
	int hpMax;
	int attack;
	int speed;

protected:

	virtual void loadSound () = 0;

	std::vector<Audio::Effect> soundEffects;

};

