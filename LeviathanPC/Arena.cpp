#include "stdafx.h"
#include "Arena.h"

#include "ErrorEnum.h"
#include "EnemiesList.h"

#include <fstream>

#include <rapidjson/filereadstream.h>

#include "Input.h"
#include "Sprite.h"
#include "Exit.h"
#include "Audio.h"
#include "CutEvent.h"
#include "GameObject.h"

using namespace std;
using namespace rapidjson;


namespace 
{
	float playerCameraMoveX, playerCameraMoveY;

	char *lastArenaSongName;
	Audio::Music *currentSong;
	bool songPlaying = false;
}


Arena* new_Arena (const char *filename) 
{
	//Alert that arena is loading
	cout << "Loading arena: " << filename << "\n";

	//Open arena file
	FILE* f = fopen (filename, "rb"); // non-Windows use "r"

	//Get file input
	char buf[65536];
	FileReadStream is (f, buf, sizeof (buf));

	//Copy file to memory, exit if failed
	if (f == NULL) 
	{
		cout << "[-] Arena: Arena file failed to load.\n";

		exit (ERROR_ARENA_LOAD_FILE);
	}

	fclose (f); //Close file

	//Parse JSON file
	Document json;
	json.Parse (buf);

	//If JSON failed to load, give error
	if (!json.IsObject ()) 
	{
		cout << "[-] Arena: JSON file failed to parse.\n";

		exit (ERROR_ARENA_PARSE_JSON);
	}

	if (json["Boss_Arena"].GetBool ()) 
	{
		return _new BossArena (json);
	} 
	else 
	{
		return _new NormalArena (json);
	}
}


Arena::Arena (rapidjson::Document &json) 
{
	//Set up visuals
	const Value &visuals_object = json["Visuals"]; //Get visuals object

	const std::string backgroundAdress = visuals_object["Background-Image"]
		.GetString (); //Get background image 
	//Create background image sprite
	this->backgroundImage = _new Sprite ((char*) backgroundAdress.c_str ()); 

	//Get background scale
	this->backgroundScale = visuals_object["Background-Scale"].GetFloat (); 

	//See if music value exists, and if so 
	if (json.HasMember ("Music")) 
	{
		//Get music value
		const Value &music = json["Music"];

		//Create buffer containing music string
		size_t size = music.GetStringLength () + 1;
		char *buf = _new char[size];
		strcpy (buf, music.GetString ());

		/*
		If string is the same, delete buffer, if not replace old song with _new
		one
		*/
		if (!strcmp (lastArenaSongName, buf)) 
		{
			//Buf is now useless, so dealocate memory
			delete[] buf;
		} 
		else 
		{
			//Allow repeat
			songPlaying = true;

			//Load up _new song and play it
			delete currentSong;
			currentSong = _new Audio::Music (buf);
			currentSong->pause (0);

			//Replace old string
			delete[] lastArenaSongName;
			lastArenaSongName = buf;
		}

	} 
	else 
	{
		//Disable song repeat (because there is none)
		songPlaying = false;

		//Clear buffers
		if (currentSong != NULL) 
		{
			delete currentSong;
			currentSong = NULL;
		}

		//Give song name NULL
		delete[] lastArenaSongName;
		lastArenaSongName = _new char[5];
		lastArenaSongName[0] = 'N';
		lastArenaSongName[1] = 'U';
		lastArenaSongName[2] = 'L';
		lastArenaSongName[3] = 'L';
		lastArenaSongName[4] = '\0';
	}

	int i = 0;

	//Up wall stuff
	const Value &up_walls_array = json["Up_Walls"];

	for (auto &wall : up_walls_array.GetArray ()) 
	{
		Rectangle rect;

		rect.setX (wall["x"].GetFloat ());
		rect.setY (wall["y"].GetFloat ());
		rect.setWidth (wall["w"].GetFloat ());
		rect.setHeight (wall["h"].GetFloat ());

		if (i == 0) 
		{
			Arena::createWallList (rect, &this->up_first, &this->up_last);

		} 
		else 
		{
			Arena::addWallList (rect, &this->up_last);
		}

		i++;
	}

	i = 0;

	//Right wall stuff
	const Value &right_walls_array = json["Right_Walls"];

	for (auto &wall : right_walls_array.GetArray ()) 
	{
		Rectangle rect;

		rect.setX (wall["x"].GetFloat ());
		rect.setY (wall["y"].GetFloat ());
		rect.setWidth (wall["w"].GetFloat ());
		rect.setHeight (wall["h"].GetFloat ());

		if (i == 0) 
		{
			Arena::createWallList (rect, &this->right_first, 
								   &this->right_last);
		} 
		else 
		{
			Arena::addWallList (rect, &this->right_last);
		}

		i++;
	}

	i = 0;

	//Down wall stuff
	const Value &down_walls_array = json["Down_Walls"];

	for (auto &wall : down_walls_array.GetArray ()) 
	{
		Rectangle rect;

		rect.setX (wall["x"].GetFloat ());
		rect.setY (wall["y"].GetFloat ());
		rect.setWidth (wall["w"].GetFloat ());
		rect.setHeight (wall["h"].GetFloat ());

		if (i == 0) 
		{
			Arena::createWallList (rect, &this->down_first, &this->down_last);
		} 
		else 
		{
			Arena::addWallList (rect, &this->down_last);
		}

		i++;
	}

	i = 0;

	//Left wall stuff
	const Value &left_walls_array = json["Left_Walls"];

	for (auto &wall : left_walls_array.GetArray ()) 
	{
		Rectangle rect;

		rect.setX (wall["x"].GetFloat ());
		rect.setY (wall["y"].GetFloat ());
		rect.setWidth (wall["w"].GetFloat ());
		rect.setHeight (wall["h"].GetFloat ());

		if (i == 0) 
		{
			Arena::createWallList (rect, &this->left_first, &this->left_last);
		} 
		else 
		{
			Arena::addWallList (rect, &this->left_last);
		}

		i++;
	}

	i = 0;

	const Value &camera_h_walls = json["Camera-Walls-H"];

	for (auto &wall : camera_h_walls.GetArray ()) 
	{
		Rectangle rect;

		rect.setX (wall["x"].GetFloat ());
		rect.setY (wall["y"].GetFloat ());
		rect.setWidth (wall["w"].GetFloat ());
		rect.setHeight (wall["h"].GetFloat ());

		if (i == 0) 
		{
			Arena::createWallList (rect, &this->choriz_first, 
								   &this->choriz_last);
		} 
		else 
		{
			Arena::addWallList (rect, &this->choriz_last);
		}

		i++;
	}

	i = 0;

	const Value &camera_v_walls = json["Camera-Walls-V"];

	for (auto &wall : camera_v_walls.GetArray ()) 
	{
		Rectangle rect;

		rect.setX (wall["x"].GetFloat ());
		rect.setY (wall["y"].GetFloat ());
		rect.setWidth (wall["w"].GetFloat ());
		rect.setHeight (wall["h"].GetFloat ());

		if (i == 0) 
		{
			Arena::createWallList (rect, &this->cvert_first, 
								   &this->cvert_last);
		} 
		else 
		{
			Arena::addWallList (rect, &this->cvert_last);
		}

		i++;
	}
}


Arena::~Arena () 
{
	delete this->backgroundImage;

	//Go through every linked list and delete them all
	struct Walls *n, *m;

	//Delete all up walls
	n = this->up_first;

	while (n) 
	{
		m = n->next;

		delete n;

		n = m;
	}

	//Delete all right walls
	n = this->right_first;

	while (n) 
	{
		m = n->next;

		delete n;

		n = m;
	}

	//Delete all down walls
	n = this->down_first;

	while (n) 
	{
		m = n->next;

		delete n;

		n = m;
	}

	//Delete all left walls
	n = this->left_first;

	while (n) 
	{
		m = n->next;

		delete n;

		n = m;
	}

	//Delete camera horizontal blocker list
	n = this->choriz_first;

	while (n) 
	{
		m = n->next;

		delete n;

		n = m;
	}

	//Delete camera vertical blocker list
	n = this->cvert_first;

	while (n) 
	{
		m = n->next;

		delete n;

		n = m;
	}

	//Delete exit list
	Exit::deleteExitList ();

	//Reset camera
	Sprite::translateCamera (-playerCameraMoveX, -playerCameraMoveY);
}


void Arena::init () 
{
	//This needs to be done to setup the string so that the code can strcmp
	lastArenaSongName = _new char[1];
	lastArenaSongName[0] = '\00';

	return;
}


void Arena::exit () 
{
	delete[] lastArenaSongName;

	if (currentSong != NULL) 
	{
		delete currentSong;
	}

	return;
}


void Arena::playerMoveCamera (Rectangle hitbox, float x, float y) 
{
	struct Walls *n;

	n = this->choriz_first;

	while (n) 
	{
		if (Rectangle::rectIsColliding (hitbox, n->rect)) 
		{
			x = 0.0f;

			break;
		}

		n = n->next;
	}

	n = this->cvert_first;

	while (n)
	{
		if (Rectangle::rectIsColliding (hitbox, n->rect)) 
		{
			y = 0.0f;
		}

		n = n->next;
	}

	Sprite::translateCamera (x, y);

	return;
}


void Arena::canMove (Rectangle hitbox, bool *arr) 
{
	arr[0] = true;
	arr[1] = true;
	arr[2] = true;
	arr[3] = true;

	//Go through every linked list
	struct Walls *n;

	n = this->up_first;

	while (n) 
	{
		if (Rectangle::rectIsColliding (hitbox, n->rect)) 
		{
			arr[0] = false;

			break;
		}

		n = n->next;
	}

	n = this->right_first;

	while (n) 
	{
		if (Rectangle::rectIsColliding (hitbox, n->rect)) 
		{
			arr[1] = false;

			break;
		}

		n = n->next;
	}

	n = this->down_first;

	while (n) 
	{
		if (Rectangle::rectIsColliding (hitbox, n->rect)) 
		{
			arr[2] = false;

			break;
		}

		n = n->next;
	}

	n = this->left_first;

	while (n) 
	{
		if (Rectangle::rectIsColliding (hitbox, n->rect))
		{
			arr[3] = false;

			break;
		}

		n = n->next;
	}

	return;
}


bool Arena::rectInWalls (Rectangle hitbox) 
{
	//Go through every linked list
	struct Walls *n;

	n = this->up_first;

	while (n) 
	{
		if (Rectangle::rectIsColliding (hitbox, n->rect)) 
		{
			return true;
		}

		n = n->next;
	}

	n = this->right_first;

	while (n) 
	{
		if (Rectangle::rectIsColliding (hitbox, n->rect)) 
		{
			return true;
		}

		n = n->next;
	}

	n = this->down_first;

	while (n)
	{
		if (Rectangle::rectIsColliding (hitbox, n->rect)) 
		{
			return true;
		}

		n = n->next;
	}

	n = this->left_first;

	while (n) 
	{
		if (Rectangle::rectIsColliding (hitbox, n->rect)) 
		{
			return true;
		}

		n = n->next;
	}

	return false;
}


void Arena::update () 
{
	float cameraVX, cameraVY;

	//Reset camera if hitting O, move if not
	if (Input::keyHeld (SDL_SCANCODE_O))
	{
		Sprite::translateCamera (-playerCameraMoveX, -playerCameraMoveY);

		playerCameraMoveX = 0.0f;
		playerCameraMoveY = 0.0f;
	} 
	else 
	{
		//Get keys
		bool up = Input::keyHeld (SDL_SCANCODE_I);
		bool right = Input::keyHeld (SDL_SCANCODE_L);
		bool down = Input::keyHeld (SDL_SCANCODE_K);
		bool left = Input::keyHeld (SDL_SCANCODE_J);

		//Check direction and set it
		if (up && !right && !down && !left) 
		{
			cameraVX = 0.0f;
			cameraVY = 1.0f;
		} 
		else if (up && right && !down && !left) 
		{
			cameraVX = SQRT_2;
			cameraVY = SQRT_2;
		}
		else if (!up && right && !down && !left) 
		{
			cameraVX = 1.0f;
			cameraVY = 0.0f;
		} 
		else if (!up && right && down && !left) 
		{
			cameraVX = SQRT_2;
			cameraVY = _SQRT_2;
		} 
		else if (!up && !right && down && !left) 
		{
			cameraVX = 0.0f;
			cameraVY = -1.0f;
		} 
		else if (!up && !right && down && left) 
		{
			cameraVX = _SQRT_2;
			cameraVY = _SQRT_2;
		}
		else if (!up && !right && !down && left) 
		{
			cameraVX = -1.0f;
			cameraVY = 0.0f;
		} 
		else if (up && !right && !down && left) 
		{
			cameraVX = _SQRT_2;
			cameraVY = SQRT_2;
		} 
		else 
		{
			cameraVX = 0.0f;
			cameraVY = 0.0f;
		}

		//Scale
		cameraVX *= 0.005f;
		cameraVY *= 0.005f;

		//Make sure it's no further than 0.5 screens away from center
		if (playerCameraMoveX > 0.66f && cameraVX > 0.0f || 
			playerCameraMoveX < -0.66f && cameraVX < 0.0f) 
		{
			cameraVX = 0.0f;
		}

		if (playerCameraMoveY > 0.5f && cameraVY > 0.0f || 
			playerCameraMoveY < -0.5f && cameraVY < 0.0f)
		{
			cameraVY = 0.0f;
		}

		//Translate position
		playerCameraMoveX += cameraVX;
		playerCameraMoveY += cameraVY;
		Sprite::translateCamera (cameraVX, cameraVY);
	}

	return;
}


void Arena::render (GPU_Target *screen) 
{
	this->backgroundImage->render (screen, 0.0f, 0.0f, this->backgroundScale, 
								   NULL);

	if (songPlaying) 
	{
		currentSong->render ();
	}

	return;
}


void Arena::pause (int pause) 
{
	if (songPlaying)
		currentSong->pause (pause);


	return;
}


void Arena::clearMusic ()
{
	//Pause song
	currentSong->pause (1);

	//Make sure nothing calls song
	songPlaying = false;

	//Clear song
	delete currentSong;
	currentSong = NULL;


	return;
}


void Arena::createWallList (Rectangle data, Walls **first, Walls **last) 
{
	*first = _new Walls (data);

	*last = *first;

	return;
}


void Arena::addWallList (Rectangle data, Walls **last) 
{
	(*last)->next = _new Walls (data);

	*last = (*last)->next;

	return;
}


void Arena::createGameObjectsList (GameObject *data, GameObjects **first, 
								   GameObjects** last) 
{
	*first = _new GameObjects (data);

	*last = *first;

	return;
}


void Arena::addGameObjectsList (GameObject *data, GameObjects **last) 
{
	(*last)->next = _new GameObjects (data);

	*last = (*last)->next;

	return;
}


NormalArena::NormalArena (Document &json) : Arena (json) 
{
	int i = 0;

	const Value &exit_wall_list = json["Exits"];

	for (auto &box : exit_wall_list.GetArray ()) 
	{
		Rectangle rect;

		rect.setX (box["x"].GetFloat ());
		rect.setY (box["y"].GetFloat ());
		rect.setWidth (box["w"].GetFloat ());
		rect.setHeight (box["h"].GetFloat ());

		Exit *exit = _new Exit (
			box["location"].GetString (),
			rect,
			box["playerX"].GetFloat (),
			box["playerY"].GetFloat (),
			box["coffX"].GetFloat (),
			box["coffY"].GetFloat ()
		);

		if (i == 0) 
		{
			Exit::createExitList (exit);
		} 
		else 
		{
			Exit::addExitList (exit);
		}

		i++;
	}

	i = 0;

	const Value &event_wall_list = json["Events"];

	for (auto &eventObject : event_wall_list.GetArray ()) 
	{
		Rectangle rect;

		rect.setX (eventObject["x"].GetFloat ());
		rect.setY (eventObject["y"].GetFloat ());
		rect.setWidth (eventObject["w"].GetFloat ());
		rect.setHeight (eventObject["h"].GetFloat ());

		CutEvent *event  = _new CutEvent (
			eventObject["scene"].GetString (),
			rect
		);

		//Add event to list
		if (i == 0) 
		{
			CutEvent::createEventList (event);
		} 
		else 
		{
			CutEvent::addEventList (event);
		}

		i++;
	}

	i = 0;

	const Value &enemy_array = json["Enemies"];

	for (auto &enemies : enemy_array.GetArray ()) 
	{
		//Get enemy string
		const Value &enemyString = enemies["Type"];

		size_t size = enemyString.GetStringLength () + 1;
		char *buf = _new char[size];
		strcpy (buf, enemyString.GetString ());

		//Get enemy position
		float x = enemies["x"].GetFloat ();
		float y = enemies["y"].GetFloat ();

		//Pointer to enemy object
		GameObject *ptr = NULL;

		//Check what enemy it is
		if (!strcmp (buf, "KillerShadow"))
		{
			ptr = _new KillerShadow (x, y);
		}

		//Clear buffer
		delete[] buf;

		//Add enemy to object list
		if (i == 0) 
		{
			Arena::createGameObjectsList (ptr, &this->gameObject_first, 
										  &this->gameObject_last);
		} 
		else 
		{
			Arena::addGameObjectsList (ptr, &this->gameObject_last);
		}

		i++;
	}

	//Set camera back
	Sprite::translateCamera (playerCameraMoveX, playerCameraMoveY);
}


NormalArena::~NormalArena () 
{
	//Go through exit lists and delete
	Exit::deleteExitList ();
	CutEvent::deleteEventList ();

	//Go through every linked list and delete them all
	struct GameObjects *n, *m;

	//Delete all game objects
	n = this->gameObject_first;

	while (n) 
	{
		delete n->object;

		m = n->next;

		delete n;

		n = m;
	}
}


void NormalArena::updateGameObjects (GameObject::AIArgs args) 
{
	GameObjects *n = this->gameObject_first;

	while (n) 
	{
		n->object->update (args);

		n = n->next;
	}

	return;
}


void NormalArena::renderGameObjects (GPU_Target *screen) 
{
	GameObjects *n = this->gameObject_first;

	while (n) 
	{
		n->object->render (screen);

		n = n->next;
	}

	return;
}


bool NormalArena::damageGameObjects (Rectangle hitbox, int damage, 
									 bool destructable) 
{
	bool damageDelt = false;

	GameObjects *n = this->gameObject_first, *prev = NULL;

	//Go through every object to check
	while (n) 
	{
		//If attack hitbox hits, damage object
		if (Rectangle::rectIsColliding (*n->object->getHitbox (), hitbox)) 
		{
			//Damage object
			if (n->object->damage (damage)) 
			{
				damageDelt = true;

				delete n->object;

				if (prev == NULL) 
				{
					this->gameObject_first = n->next;
				} 
				else 
				{
					prev->next = n->next;
				}

				delete n;
				n = NULL;
			}

			//If attack is a one time hit, return true
			if (destructable)
				return true;
		}

		if (n != NULL) 
		{
			prev = n;
			n = n->next;
		}
	}

	this->gameObject_last = n;

	return damageDelt;
}


bool NormalArena::damageGameObjects (float cx, float cy, float cradius, 
									 int damage, bool destructable) 
{
	GameObjects *n = this->gameObject_first, *prev = NULL;

	//Go through every object to check
	while (n) 
	{
		//If attack hitbox hits, damage object
		if (Rectangle::rectInCircle (*n->object->getHitbox (), cx, cy, 
			cradius))
		{
			//Damage object
			if (n->object->damage (damage)) 
			{
				delete n->object;

				if (prev == NULL) 
				{
					this->gameObject_first = n->next;
				} 
				else 
				{
					prev->next = n->next;
				}

				delete n;
				n = NULL;
			}

			//If attack is a one time hit, return true
			if (destructable)
				return true;
		}

		if (n != NULL) 
		{
			prev = n;
			n = n->next;
		}
	}

	this->gameObject_last = n;

	return false;
}


BossArena::BossArena (rapidjson::Document &json) : Arena (json) 
{

}


BossArena::~BossArena () 
{

}


void BossArena::updateGameObjects (GameObject::AIArgs args) 
{
	return;
}


void BossArena::renderGameObjects (GPU_Target *screen)
{
	return;
}


bool BossArena::damageGameObjects (Rectangle hitbox, int damage,
								   bool destructable) 
{
	return false;
}


bool BossArena::damageGameObjects (float cx, float cy, float cradius, 
								   int damage, bool destructable) 
{
	return false;
}
