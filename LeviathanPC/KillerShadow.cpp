#include "stdafx.h"
#include "KillerShadow.h"

#include "Arena.h"
#include "Input.h"

KillerShadow::KillerShadow (float x, float y) {

	this->spritesheet = new SpriteSheet ((char*) "assets/enemies/basic/ShadowPlayer.png", 4, 8);

	this->hitbox = new Rectangle (x, y, 0.05f, 0.05f);

	//Setup AI
	this->objectAIState.currentAIAction = &KillerShadow::aStar;
	this->objectAIState.state = 0x0001;
	this->objectAIState.range = 0.02f;

}

KillerShadow::~KillerShadow () {



}

bool KillerShadow::update (AIArgs args) {

	//If the object is on screen, execute AI
	if (this->hitbox->rectOnScreen ()) {

		(this->*(this->objectAIState.currentAIAction)) (this->objectAIState, args);

		args.activeArena->canMove (*this->hitbox, this->canMove); //Get if player can wall

		//Get player velocity
		switch (this->direction) {

		case UP:
			this->vx = 0.0f;
			this->vy = -1.0f * canMove[0];
			this->spriteDirection = 0;
			break;

		case UP_RIGHT:
			this->vx = SQRT_2 * canMove[1];
			this->vy = _SQRT_2 * canMove[0];
			this->spriteDirection = 0;
			break;

		case RIGHT:
			this->vx = 1.0f * canMove[1];
			this->vy = 0.0f;
			this->spriteDirection = 1;
			break;

		case DOWN_RIGHT:
			this->vx = SQRT_2 * canMove[1];
			this->vy = SQRT_2 * canMove[2];
			this->spriteDirection = 1;
			break;

		case DOWN:
			this->vx = 0.0f;
			this->vy = 1.0f * canMove[2];
			spriteDirection = 2;
			break;

		case DOWN_LEFT:
			this->vx = _SQRT_2 * canMove[3];
			this->vy = SQRT_2 * canMove[2];
			this->spriteDirection = 3;
			break;

		case LEFT:
			this->vx = -1.0f * canMove[3];
			this->vy = 0.0f;
			this->spriteDirection = 3;
			break;

		case UP_LEFT:
			this->vx = _SQRT_2 * canMove[3];
			this->vy = _SQRT_2 * canMove[0];
			this->spriteDirection = 0;
			break;

		default:
			this->vx = 0.0f;
			this->vy = 0.0f;
			break;

		}

		//Adjust based of of delta time
		this->vx *= (float) (0.005f *  Input::getDelta ());
		this->vy *= (float) (0.005f *  Input::getDelta ());

		this->hitbox->translate (this->vx, this->vy);

	}

	return false;

}

void KillerShadow::render (GPU_Target *screen) {

	Uint8 animation = 0;

	if (this->vx > 0 || this->vy > 0) {

		animation = (int) (SDL_GetTicks () * 0.012) % 8;

	}

	this->spritesheet->render (screen, this->hitbox->getX (), this->hitbox->getY (), 2.0f, this->spriteDirection, animation);

}


void KillerShadow::death () {



}

void KillerShadow::loadSound () {



}
