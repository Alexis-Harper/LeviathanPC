#include "stdafx.h"
#include "Arena.h"

#include "ErrorEnum.h"
#include <fstream>

#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

using namespace std;
using namespace rapidjson;

Arena::Arena () {

	//Create borders
	this->createWallList (new Rectangle (0.0f, 0.0f, 1.0f, 0.0f), &this->up_first, &this->up_last);
	this->createWallList (new Rectangle (1.0f, 0.0f, 0.0f, 1.0f), &this->right_first, &this->right_last);
	this->createWallList (new Rectangle (0.0f, 1.0f, 1.0f, 0.0f), &this->down_first, &this->down_last);
	this->createWallList (new Rectangle (0.0f, 0.0f, 0.0f, 1.0f), &this->left_first, &this->left_last);

}

Arena::Arena (char *filename) {

	FILE* f = fopen (filename, "rb"); // non-Windows use "r"

	char buf[65536];
	FileReadStream is (f, buf, sizeof (buf));

	//Copy file to memory, exit if failed
	if (f == NULL) {

		cout << "[-] Arena: Arena file failed to load.\n";

		exit (ERROR_ARENA_LOAD_FILE);

	}

	fclose (f); //Close file*/

	Document json;
	json.Parse (buf);

	if (!json.IsObject ()) {

		cout << "[-] Arena: JSON file failed to parse.\n";

		exit (ERROR_ARENA_PARSE_JSON);

	}

	int i = 0;

	//Up wall stuff
	const Value &up_walls_array = json["Up_Walls"];

	for (auto &wall : up_walls_array.GetArray ()) {

		Rectangle *rect = new Rectangle();

		rect->setX (wall["x"].GetFloat ());
		rect->setY (wall["y"].GetFloat ());
		rect->setWidth (wall["w"].GetFloat ());
		rect->setHeight (wall["h"].GetFloat ());

		if (i == 0) {

			Arena::createWallList (rect, &this->up_first, &this->up_last);

		} else {

			Arena::addWallList (rect, &this->up_last);

		}

		i++;

	}

	i = 0;

	//Right wall stuff
	const Value &right_walls_array = json["Right_Walls"];

	for (auto &wall : right_walls_array.GetArray ()) {

		Rectangle *rect = new Rectangle ();

		rect->setX (wall["x"].GetFloat ());
		rect->setY (wall["y"].GetFloat ());
		rect->setWidth (wall["w"].GetFloat ());
		rect->setHeight (wall["h"].GetFloat ());

		if (i == 0) {

			Arena::createWallList (rect, &this->right_first, &this->right_last);

		} else {

			Arena::addWallList (rect, &this->right_last);

		}

		i++;

	}

	i = 0;

	//Down wall stuff
	const Value &down_walls_array = json["Down_Walls"];

	for (auto &wall : down_walls_array.GetArray ()) {

		Rectangle *rect = new Rectangle ();

		rect->setX (wall["x"].GetFloat ());
		rect->setY (wall["y"].GetFloat ());
		rect->setWidth (wall["w"].GetFloat ());
		rect->setHeight (wall["h"].GetFloat ());

		if (i == 0) {

			Arena::createWallList (rect, &this->down_first, &this->down_last);

		} else {

			Arena::addWallList (rect, &this->down_last);

		}

		i++;

	}

	i = 0;

	//Left wall stuff
	const Value &left_walls_array = json["Left_Walls"];

	for (auto &wall : left_walls_array.GetArray ()) {

		Rectangle *rect = new Rectangle ();

		rect->setX (wall["x"].GetFloat ());
		rect->setY (wall["y"].GetFloat ());
		rect->setWidth (wall["w"].GetFloat ());
		rect->setHeight (wall["h"].GetFloat ());

		if (i == 0) {

			Arena::createWallList (rect, &this->left_first, &this->left_last);

		} else {

			Arena::addWallList (rect, &this->left_last);

		}

		i++;

	}

	i = 0;

}

Arena::~Arena () {

	//Go through every linked list and delete them all
	struct Walls *n, *m;

	n = this->up_first;

	while (n) {

		delete n->rect;

		m = n->next;

		delete n;

		n = m;

	}

	n = this->right_first;

	while (n) {

		delete n->rect;

		m = n->next;

		delete n;

		n = m;

	}

	n = this->down_first;

	while (n) {

		delete n->rect;

		m = n->next;

		delete n;

		n = m;

	}

	n = this->left_first;

	while (n) {

		delete n->rect;

		m = n->next;

		delete n;

		n = m;

	}

}

bool* Arena::canMove (Rectangle hitbox) {

	//Create array to return
	static bool ret[4];

	ret[0] = true;
	ret[1] = true;
	ret[2] = true;
	ret[3] = true;

	//Go through every linked list
	struct Walls *n;

	n = this->up_first;

	while (n) {

		if (Rectangle::rectIsColliding (hitbox, *n->rect)) {

			ret[0] = false;

			break;

		}

		n = n->next;

	}

	n = this->right_first;

	while (n) {

		if (Rectangle::rectIsColliding (hitbox, *n->rect)) {

			ret[1] = false;

			break;

		}

		n = n->next;

	}

	n = this->down_first;

	while (n) {

		if (Rectangle::rectIsColliding (hitbox, *n->rect)) {

			ret[2] = false;

			break;

		}

		n = n->next;

	}

	n = this->left_first;

	while (n) {

		if (Rectangle::rectIsColliding (hitbox, *n->rect)) {

			ret[3] = false;

			break;

		}

		n = n->next;

	}

	return ret;

}

void Arena::createWallList (Rectangle *data, Walls **first, Walls **last) {

	*first = new Walls (data);

	*last = *first;

}

void Arena::addWallList (Rectangle *data, Walls **last) {

	Walls *prev = *last;

	*last = new Walls (data);

	prev->next = *last;

}

void Arena::createGameObjectsList (GameObject *data, GameObjects **first, GameObjects** last) {

	*first = new GameObjects (data);

	*last = *first;

}

void Arena::addGameObjectsList (GameObject *data, GameObjects **last) {

	GameObjects *prev = *last;

	*last = new GameObjects (data);

	prev->next = *last;

}
