#pragma once

#include "Audio.h"

class GameObject {

public:

	GameObject ();
	~GameObject ();

	//This is good
	virtual bool update () = 0;
	virtual void render () = 0;

	bool damage (int damage);

	virtual void death () = 0;

	int getHp ();
	int getHpMax ();
	int getAttack ();
	int getSpeed ();

	void setHp (int hp);
	void setHpMax (int hpMax);
	void setAttack (int attack);
	void setSpeed (int speed);

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

