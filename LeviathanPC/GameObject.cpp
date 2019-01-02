#include "stdafx.h"
#include "GameObject.h"

#include <map>
#include <list>

#include "Arena.h"

#define tstBit(flag, bit) (flag & (1 << bit))
#define setBit(flag, bit) flag = (flag | (1 << bit))
#define clrBit(flag, bit) flag = (flag & ~(1 << bit))

enum Flags {

	AI_STATE_FLAG_BODY_ATTACK

};

GameObject::GameObject () {



}

GameObject::~GameObject () {

	

}

bool GameObject::damage (int attack) {

	if (attack >= this->hp) {

		this->death ();

		return true;

	} else {

		this->hp -= attack;

		return false;

	}

}

int GameObject::getHp () {

	return this->hp;

}

int GameObject::getHpMax () {

	return this->hpMax;

}

int GameObject::getAttack () {

	return this->attack;

}

int GameObject::getSpeed () {

	return this->speed;

}

void GameObject::setHp (int value) {

	this->hp = value;

}

void GameObject::setHpMax (int value) {

	this->hpMax = value;

}

void GameObject::setAttack (int value) {

	this->attack = value;

}

void GameObject::setSpeed (int value) {

	this->speed = value;

}

void GameObject::executeAI (AIState &objectAIState, AIArgs args) {

	//If the object is on screen, execute AI
	if (this->hitbox->rectOnScreen ()) {

		(this->*(this->objectAIState.currentAIAction)) (this->objectAIState, args);

	}

}

void GameObject::aStar (AIState &objectAIState, AIArgs args) {

	//Basic var declaration
	double angle = 0.0f;

	float xToPlayer = args.player->getHixbox ().getX () - this->hitbox->getX ();
	float yToPlayer = args.player->getHixbox ().getY () - this->hitbox->getY ();

	//Set test box rect
	Rectangle testBox;

	testBox.setX (this->hitbox->getX () + 0.25f);
	testBox.setY (this->hitbox->getY () + 0.25f);
	testBox.setWidth (0.5f);
	testBox.setHeight (0.5f);

	//If player is 
	if (args.activeArena->rectInWalls (testBox)) {

		//Set angle to angle to player
		angle = atan2 (-yToPlayer, xToPlayer);

	} else {

		//TODO Implement A* pathfinding algorithm to find new angle

		//Lambada for A* heuristic
		auto heuristic = [](float startX, float startY, float nodeX, float nodeY, float destX, float destY) {

			//dx = node.x - player.x
			float dx1 = nodeX - destX;
			
			//dy = node.y - player.y
			float dy1 = nodeY - destY;
			
			//Calculate vector from start
			float dx2 = nodeX - startX;
			float dy2 = nodeY - startY;

			//Calculate abs of cross product (tiebreaker that favors straight lines)
			float cross = ((dx1 * dy2) - (dy1 * dx2));

			//Use abs of derivatives
			dx1 = (dx1 >= 0) ? dx1 : -dx1;
			dy1 = (dy1 >= 0) ? dy1 : -dy1;

			//D * (dx + dy) + (D2 - 2 * D) * min (dx, dy) where D = 1 & D2 = sqrt (2)
			float heuristic = (dx1 + dy1) - (0.4142135f * ((dy1 < dx1) ? dy1 : dx1));

			//Add tiebreaker (reduces number of checked tiles)
			heuristic += cross * 0.01f; 

			return heuristic;

		};

		/* Start and finish coords
			this->hitbox->getX ()
			this->hitbox->getY ()
			args.player->getHixbox ().getX ()
			args.player->getHixbox ().getY ()
		*/

		//Map for coordinates around it
		//std::map<std::pair<int, int>, float> map;

		struct Point {

			float x, y;

			float f, g;

			Point *lastPoint;

			Point (float i, float j, float k) : x (i), y (j), g (k) { lastPoint = NULL; };

		};

		//Open and closed set arrays
		std::list<struct Point> openSet;
		std::list<struct Point> closedSet;

		//Add starting position to openSet
		struct Point startingPoint = Point (this->hitbox->getX (), this->hitbox->getY (), 0);
		startingPoint.f = heuristic (this->hitbox->getX (), this->hitbox->getY (), this->hitbox->getX (), this->hitbox->getY (), args.player->getHixbox ().getX (), args.player->getHixbox ().getY ());
		openSet.push_back (startingPoint);

		while (1) {

			//Find the part with the smallest f value
			std::list<struct Point>::iterator lowest = openSet.begin ();

			//Go through list and check if 
			for (std::list<struct Point>::iterator i = openSet.begin (); ++i != openSet.end (); ) {

				//If i is lower than current lowest, change lowest to i
				if ((*i).f < (*lowest).f) {

					lowest = i;

				}

			}

			//Check if destination is found
			if ((*lowest).x <= args.player->getHixbox ().getX () &&
				(*lowest).y <= args.player->getHixbox ().getY () &&
				(*lowest).x + 0.02 >= args.player->getHixbox ().getX () &&
				(*lowest).y + 0.02 >= args.player->getHixbox ().getY ()) {

				Point *n = (*lowest).lastPoint;

				while (n && n->lastPoint && (n->lastPoint->x != this->hitbox->getX ()) && (n->lastPoint->y != this->hitbox->getY ())) {

					n = n->lastPoint;

				}

				//If already on player, continue to follow, if not, follow path
				if (n == NULL) {

					angle = atan2 (-yToPlayer, xToPlayer);

				} else {

					angle = atan2 (n->y - this->hitbox->getY (), this->hitbox->getX () - n->x);

				}

				break;

			}

			//Move lowest from openSet to closedSet
			Point current = *lowest;
			openSet.erase (lowest);
			closedSet.push_back (current);

			//Add neibors
			{
				std::list<struct Point> neibors;

				neibors.push_back (Point (current.x + 0.025f, current.y, current.g + 1.0f)); //Adjacent
				neibors.push_back (Point (current.x - 0.025f, current.y, current.g + 1.0f));
				neibors.push_back (Point (current.x, current.y + 0.025f, current.g + 1.0f));
				neibors.push_back (Point (current.x, current.y - 0.025f, current.g + 1.0f));

				neibors.push_back (Point (current.x + 0.025f, current.y + 0.025f, current.g + 1.4142135f)); //Diagonals
				neibors.push_back (Point (current.x + 0.025f, current.y - 0.025f, current.g + 1.4142135f));
				neibors.push_back (Point (current.x - 0.025f, current.y + 0.025f, current.g + 1.4142135f));
				neibors.push_back (Point (current.x - 0.025f, current.y - 0.025f, current.g + 1.4142135f));

				//See if any neibors are in closed set, and if they are, remove them
				for (std::list<struct Point>::iterator i = neibors.begin (); ++i != neibors.end (); ) {

					//If tile is in wall, forget about it
					if (args.activeArena->rectInWalls (Rectangle ((*i).x, (*i).y, 0.025f, 0.025f))) {

						neibors.erase (i);

						goto doneChecking;

					}

					//Check if in closed set, and if it is, remove it
					for (std::list<struct Point>::iterator j = closedSet.begin (); ++j != closedSet.end (); ) {

						if ((*i).x == (*j).x && (*i).y == (*j).y) {

							neibors.erase (i);

							goto doneChecking;

						}

					}

					//Check if in open set, and if so, keep most efficent
					if (!openSet.empty()) {

						for (std::list<struct Point>::iterator k = openSet.begin (); ++k != openSet.end (); ) {

							if ((*i).x == (*k).x && (*i).y == (*k).y) {

								if ((*i).g < (*k).g) {

									openSet.erase (k);

									break;

								} else {

									neibors.erase (i);

									goto doneChecking;

								}

							}

						}

					}

					//If it still exists, finish calculations
					(*i).f = (*i).g + heuristic (this->hitbox->getX (), this->hitbox->getY (), (*i).x, (*i).y, args.player->getHixbox ().getX (), args.player->getHixbox ().getY ()); //Calc. f

					(*i).lastPoint = &(closedSet.back ()); //Odd notation, but essentially have a reversed linked list as well

				}

			doneChecking:

				for (std::list<struct Point>::iterator i = neibors.begin (); ++i != neibors.end (); ) {

					openSet.push_back (*i);

				}

			}

			//If there have been enough checked, give up and just go to player;
			if (closedSet.size () > 32) {

				//Set angle to angle to player
				angle = atan2 (-yToPlayer, xToPlayer);

				break;

			}

		}

	}

	//Set direction enum
	if ((angle <= (5 * M_PI / 8) && angle >= (3 * M_PI / 8))) {

		this->direction = UP;

	} else if ((angle <= (3 * M_PI / 8) && angle >= (M_PI / 8))) {

		this->direction = UP_RIGHT;

	} else if ((angle <= (M_PI / 8) && angle >= (-M_PI / 8))) {

		this->direction = RIGHT;

	} else if ((angle <= (-M_PI / 8) && angle >= (-3 * M_PI / 8))) {

		direction = DOWN_RIGHT;

	} else if ((angle <= (-3 * M_PI / 8) && angle >= (-5 * M_PI / 8))) {

		this->direction = DOWN;

	} else if ((angle <= (-5 * M_PI / 8) && angle >= (-7 * M_PI / 8))) {

		this->direction = DOWN_LEFT;

	} else if ((angle <= (-7 * M_PI / 8) || angle >= (7 * M_PI / 8))) {

		this->direction = LEFT;

	} else if ((angle <= (7 * M_PI / 8) && angle >= (5 * M_PI / 8))) {

		this->direction = UP_LEFT;

	} else {

		this->direction = NONE;

	}

	if ((sqrt (xToPlayer * xToPlayer + yToPlayer * yToPlayer) >= objectAIState.range)) {

		if (tstBit (objectAIState.state, AI_STATE_FLAG_BODY_ATTACK)) {

			objectAIState.currentAIAction = &GameObject::bodyAttack;

		}

	}

}

void GameObject::bodyAttack (AIState &objectAIState, AIArgs args) {

	this->aStar (objectAIState, args);

	if (Rectangle::rectIsColliding (*this->hitbox, args.player->getHixbox ())) {

		args.player->damage (10, args.healthBar);

	}

}
