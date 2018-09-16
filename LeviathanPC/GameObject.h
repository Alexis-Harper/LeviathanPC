#pragma once

class GameObject {

public:

	GameObject ();
	~GameObject ();

	//This is good
	virtual bool update () = 0;
	virtual void render () = 0;

	bool damage (int);

	virtual void death () = 0;

private:

	//Stats
	int hp;
	int hpMax;
	int attack;
	int speed;

protected:

	virtual void loadSound () = 0;

};

