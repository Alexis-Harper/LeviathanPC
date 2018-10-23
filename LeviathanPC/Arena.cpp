#include "stdafx.h"
#include "Arena.h"

#include "ErrorEnum.h"
#include <fstream>

#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

#include "Input.h"
#include "Sprite.h"
#include "Exit.h"
#include "Audio.h"

using namespace std;
using namespace rapidjson;

namespace {

	float playerCameraMoveX, playerCameraMoveY;

	char *lastArenaSongName;
	Audio::Music *currentSong;
	bool songPlaying = false;

}

Arena::Arena () {

	//Create borders
	this->createWallList (new Rectangle (0.0f, 0.0f, 1.0f, 0.0f), &this->up_first, &this->up_last);
	this->createWallList (new Rectangle (1.0f, 0.0f, 0.0f, 1.0f), &this->right_first, &this->right_last);
	this->createWallList (new Rectangle (0.0f, 1.0f, 1.0f, 0.0f), &this->down_first, &this->down_last);
	this->createWallList (new Rectangle (0.0f, 0.0f, 0.0f, 1.0f), &this->left_first, &this->left_last);

}

Arena::Arena (const char *filename) {

	cout << "Loading arena: " << filename << "\n";

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

	//Set up visuals
	const Value &visuals_object = json["Visuals"];

	const std::string backgroundAdress = visuals_object["Background-Image"].GetString ();
	this->backgroundImage = new Sprite ((char*) backgroundAdress.c_str());

	this->backgroundScale = visuals_object["Background-Scale"].GetFloat ();

	//See if music value exists, and if so 
	if (json.HasMember("Music")) {

		//Get music value
		const Value &music = json["Music"];

		//Create buffer containing music string
		size_t size = music.GetStringLength () + 1;
		char *buf = new char[size];
		strcpy (buf, music.GetString ());

		//If string is the same, delete buffer, if not replace old song with new one
		if (!strcmp (lastArenaSongName, buf)) {

			//Buf is now useless, so dealocate memory
			delete[] buf;

		} else {

			//Load up new song and play it
			delete currentSong;
			currentSong = new Audio::Music (buf);
			currentSong->pause (0);

			//Replace old string
			delete[] lastArenaSongName;
			lastArenaSongName = buf;

		}

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

	const Value &camera_h_walls = json["Camera-Walls-H"];

	for (auto &wall : camera_h_walls.GetArray ()) {

		Rectangle *rect = new Rectangle ();

		rect->setX (wall["x"].GetFloat ());
		rect->setY (wall["y"].GetFloat ());
		rect->setWidth (wall["w"].GetFloat ());
		rect->setHeight (wall["h"].GetFloat ());

		if (i == 0) {

			Arena::createWallList (rect, &this->choriz_first, &this->choriz_last);

		} else {

			Arena::addWallList (rect, &this->choriz_last);

		}

		i++;

	}

	i = 0;

	const Value &camera_v_walls = json["Camera-Walls-V"];

	for (auto &wall : camera_v_walls.GetArray ()) {

		Rectangle *rect = new Rectangle ();

		rect->setX (wall["x"].GetFloat ());
		rect->setY (wall["y"].GetFloat ());
		rect->setWidth (wall["w"].GetFloat ());
		rect->setHeight (wall["h"].GetFloat ());

		if (i == 0) {

			Arena::createWallList (rect, &this->cvert_first, &this->cvert_last);

		} else {

			Arena::addWallList (rect, &this->cvert_last);

		}

		i++;

	}

	i = 0;

	const Value &exit_wall_list = json["Exits"];

	for (auto &box : exit_wall_list.GetArray ()) {

		Rectangle rect;

		rect.setX (box["x"].GetFloat ());
		rect.setY (box["y"].GetFloat ());
		rect.setWidth (box["w"].GetFloat ());
		rect.setHeight (box["h"].GetFloat ());

		Exit *exit = new Exit (

			box["location"].GetString (),
			rect,
			box["playerX"].GetFloat (),
			box["playerY"].GetFloat (),
			box["coffX"].GetFloat (),
			box["coffY"].GetFloat ()

		);

		if (i == 0) {

			Exit::createExitList (exit);

		} else {

			Exit::addExitList (exit);

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

	n = this->choriz_first;

	while (n) {

		delete n->rect;

		m = n->next;

		delete n;

		n = m;

	}

	n = this->cvert_first;

	while (n) {

		delete n->rect;

		m = n->next;

		delete n;

		n = m;

	}

	Exit::deleteExitList ();

}

void Arena::init () {

	lastArenaSongName = new char[1];
	lastArenaSongName[0] = '\00';

}

void Arena::update () {

	float cameraVX, cameraVY;

	//Reset camera if hitting O, move if not
	if (Input::keyHeld (SDL_SCANCODE_O)) {

		Sprite::translateCamera (-playerCameraMoveX, -playerCameraMoveY);

		playerCameraMoveX = 0.0f;
		playerCameraMoveY = 0.0f;

	} else {

		//Get keys
		bool up = Input::keyHeld (SDL_SCANCODE_I);
		bool right = Input::keyHeld (SDL_SCANCODE_L);
		bool down = Input::keyHeld (SDL_SCANCODE_K);
		bool left = Input::keyHeld (SDL_SCANCODE_J);

		//Check direction and set it
		if (up && !right && !down && !left) {

			cameraVX = 0.0f;
			cameraVY = 1.0f;

		} else if (up && right && !down && !left) {

			cameraVX = SQRT_2;
			cameraVY = SQRT_2;

		} else if (!up && right && !down && !left) {

			cameraVX = 1.0f;
			cameraVY = 0.0f;

		} else if (!up && right && down && !left) {

			cameraVX = SQRT_2;
			cameraVY = _SQRT_2;

		} else if (!up && !right && down && !left) {

			cameraVX = 0.0f;
			cameraVY = -1.0f;

		} else if (!up && !right && down && left) {

			cameraVX = _SQRT_2;
			cameraVY = _SQRT_2;

		} else if (!up && !right && !down && left) {

			cameraVX = -1.0f;
			cameraVY = 0.0f;

		} else if (up && !right && !down && left) {

			cameraVX = _SQRT_2;
			cameraVY = SQRT_2;

		} else {

			cameraVX = 0.0f;
			cameraVY = 0.0f;

		}

		//Scale
		cameraVX *= 0.005f;
		cameraVY *= 0.005f;

		//Make sure it's no further than 0.5 screens away from center
		if (playerCameraMoveX > 0.66f && cameraVX > 0.0f || playerCameraMoveX < -0.66f && cameraVX < 0.0f) {

			cameraVX = 0.0f;

		} 

		if (playerCameraMoveY > 0.5f && cameraVY > 0.0f || playerCameraMoveY < -0.5f && cameraVY < 0.0f) {

			cameraVY = 0.0f;

		}

		//Translate position
		playerCameraMoveX += cameraVX;
		playerCameraMoveY += cameraVY;
		Sprite::translateCamera (cameraVX, cameraVY);

	}

}

void Arena::render (GPU_Target *screen) {

	this->backgroundImage->render (screen, 0.0f, 0.0f, this->backgroundScale, NULL);

	if (songPlaying) {

		currentSong->render ();

	}

}

void Arena::playerMoveCamera (Rectangle hitbox, float x, float y) {

	struct Walls *n;

	n = this->choriz_first;

	while (n) {

		if (Rectangle::rectIsColliding (hitbox, *n->rect)) {

			x = 0.0f;

			break;

		}

		n = n->next;

	}

	n = this->cvert_first;

	while (n) {

		if (Rectangle::rectIsColliding (hitbox, *n->rect)) {

			y = 0.0f;

		}

		n = n->next;

	}

	Sprite::translateCamera (x, y);

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

void Arena::pause (int pause) {

	currentSong->pause (pause);

}

void Arena::createWallList (Rectangle *data, Walls **first, Walls **last) {

	*first = new Walls (data);

	*last = *first;

}

void Arena::addWallList (Rectangle *data, Walls **last) {

	struct Walls *prev = *last;

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
