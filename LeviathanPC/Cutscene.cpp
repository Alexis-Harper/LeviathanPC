#include "stdafx.h"
#include "Cutscene.h"

#include "ErrorEnum.h"
#include "ControllerDefines.h"

#include <fstream>

#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

#include "Input.h"

using namespace std;
using namespace rapidjson;

Cutscene::Cutscene (const char *filename) {

	//Load up cutscenene file
	cout << "Loading cutscene: " << filename << "\n";

	FILE *f = fopen (filename, "rb"); // non-Windows use "r"

	//Get file input
	char buf[65536];
	FileReadStream is (f, buf, sizeof (buf));

	//Copy file to memory, exit if failed
	if (f == NULL) {

		cout << "[-] Cutscene: Cutscene JSON failed to load.\n";

		exit (ERROR_CUTSCENE_LOAD_FILE);

	}

	fclose (f); //Close file

	//Parse JSON
	Document json;
	json.Parse (buf);

	if (!json.IsObject ()) {

		cout << "[-] Cutscene: JSON file failed to parse.\n";

		exit (ERROR_CUTSCENE_PARSE_JSON);

	}

	//Load up audio
	const Value &music_object = json["Music"];

	//Create buffer containing music string
	size_t size = music_object.GetStringLength () + 1;
	char *musicBuf = _new char[size];
	strcpy (musicBuf, music_object.GetString ());

	//Load up audio file and play it
	this->audio = _new Audio::Audio (musicBuf, NULL);
	this->audio->pause (0);
	delete[] musicBuf;

	//Iterator
	int i = 0;

	//Gets array of tile objects
	const Value &tile_array = json["Tile_Array"];

	for (auto &wall : tile_array.GetArray ()) {

		const Value &tile_image_name = wall["Image_Name"];

		//Create buffer containing music string
		size_t size = tile_image_name.GetStringLength () + 1;
		char *image_name = _new char[size];
		strcpy (image_name, tile_image_name.GetString ());

		//Create cutscene tile
		CutTile *newTile = _new CutTile (image_name, wall["Scale"].GetFloat ());

		delete[] image_name;

		//Set timing
		newTile->setFadeIn (wall["Fade_In"].GetFloat ());
		newTile->setStayTime (wall["Stay_Time"].GetFloat ());
		newTile->setFadeOut (wall["Fade_Out"].GetFloat ());

		//Add to list
		if (i == 0) {

			Cutscene::createTileList (newTile, &this->first_tile, &this->last_tile);

		} else {

			Cutscene::addTileList (newTile, &this->last_tile);

		}

		i++;

	}

	i = 0;

	//Checks if dialogue exists
	if (json.HasMember ("Text_Array")) {

		//Set dialogue playing to true
		this->dialogue_playing = true;

		//Gets array of dialogue objects
		const Value &text_array = json["Text_Array"];

		for (auto &text_data : text_array.GetArray ()) {

			const Value &dialogue_text = text_data["Dialogue"];

			//Create buffer containing music string
			size_t size = dialogue_text.GetStringLength () + 1;
			char *text = _new char[size];
			strcpy (text, dialogue_text.GetString ());

			//Add to list
			if (i == 0) {

				Cutscene::createTextList (text, text_data["Time"].GetFloat (), &this->first_text, &this->last_text);

			} else {

				Cutscene::addTextList (text, text_data["Time"].GetFloat (), &this->last_text);

			}

			i++;

		}

	} else {

		//Tell it not to play dialogue
		this->dialogue_playing = false;

	}

	//Get next arena 
	const Value &next_arena_value = json["Next_Arena"];

	//Get arena location
	const Value &location = next_arena_value["location"];

	size = location.GetStringLength () + 1;
	this->nextArena = _new char[size];
	strcpy (this->nextArena, location.GetString ());

	//Get location offsets
	this->playerX = next_arena_value["playerX"].GetFloat ();
	this->playerY = next_arena_value["playerY"].GetFloat ();
	this->cameraOffsetX = next_arena_value["coffX"].GetFloat ();
	this->cameraOffsetY = next_arena_value["coffY"].GetFloat ();

	//Set primary and secondary tiles
	this->current = this->first_tile;

	//Set timing
	this->current_fade_in = this->current->tile->getFadeIn ();
	this->current_stay_time = this->current->tile->getStayTime ();
	this->current_fade_out = this->current->tile->getFadeOut ();

	//Set text list info
	this->current_text = this->first_text;
	this->dialogue_timer = this->current_text->time;


	//Set 
	if (Input::controllerUsed ()) {

		this->skipButtonSprite = _new Sprite ((char*) "assets/cutscenes/images/Skip_START.png");

	} else {

		this->skipButtonSprite = _new Sprite ((char*) "assets/cutscenes/images/Skip_ENTER.png");

	}

	this->skipButtonSprite->setAlpha (0);

	this->skipFrames = 0.0f;

}

Cutscene::~Cutscene () {

	cout << "Deleted cutscene";

	delete this->skipButtonSprite;
	delete[] this->nextArena;

	//Make sure it's alive before killing (to prevent repeats causing memory problems)
	delete this->audio;

	{
		struct TileList *n, *m;

		n = this->first_tile;

		while (n) {

			delete n->tile;

			m = n->next;

			delete n;

			n = m;

		}

	}

	{
		struct TextList *n, *m;

		n = this->first_text;

		while (n) {

			delete[] n->text;

			m = n->next;

			delete n;

			n = m;

		}

	}

}

bool Cutscene::render (GPU_Target *screen, Arena **arena, Player *player, GameState *gameState) {

	//Calculate what the render should be

	//Fade in stage
	if (this->current_fade_in > 0.0f) { 

		//Check if time is up
		if (this->current_fade_in <= Input::getDelta ()) {

			//Set fade in to 0.0f
			this->current_fade_in = 0.0f;

			//Set alpha to full
			this->current->tile->setAlpha (255);

		} else {

			//Set fade in to _new time
			this->current_fade_in -= (float) Input::getDelta ();

			//Set alpha to new
			this->current->tile->setAlpha ((Uint8) (255 * (this->current->tile->getFadeIn () - this->current_fade_in) / this->current->tile->getFadeIn ()));

		}

	//Stay time stage
	} else if (this->current_stay_time > 0.0f) { 

		//Check if time is up
		if (this->current_stay_time <= Input::getDelta ()) {

			//Set stay time to 0.0f
			this->current_stay_time = 0.0f;

		} else {

			//Set stay time to _new time
			this->current_stay_time -= (float) Input::getDelta ();

		}

	//Fade out stage
	} else if (this->current_fade_out > 0.0f) {

		//Check if time is up
		if (this->current_fade_out <= Input::getDelta ()) {

			if (this->current->next != NULL) {

				//Go to next tile
				this->current = this->current->next;

				//Set timing
				this->current_fade_in = this->current->tile->getFadeIn ();
				this->current_stay_time = this->current->tile->getStayTime ();
				this->current_fade_out = this->current->tile->getFadeOut ();

			} else {

				//Set player position
				player->setPosition (this->getPlayerX (), this->getPlayerY ());

				//Set camera position (with offset)
				Sprite::setCamera (this->getCamPosX (), this->getCamPosY ());

				//Replace arena
				*arena = new_Arena (this->nextArena);

				//Set game state
				*gameState = GameState::GAME;

				return true;

			}

		} else {

			//Set fade in to _new time
			this->current_fade_out -= (float) Input::getDelta ();

			//Set alpha to new
			this->current->tile->setAlpha ((Uint8) (255 * this->current_fade_out / this->current->tile->getFadeOut ()));

		}

	}

	if (this->skipFrames == 0.0f) {

		if (Input::controllerUsed ()) {

			if (Input::buttonHeld (SDL_CONTROLLER_START)) {

				this->skipFrames = 180.0f;

				this->skipButtonSprite->setAlpha (255);

			}

		} else {

			if (Input::keyHeld (SDL_SCANCODE_RETURN)) {

				this->skipFrames = 180.0f;

				this->skipButtonSprite->setAlpha (255);

			}

		}

	} else {

		if (this->skipFrames > Input::getDelta ()) {

			this->skipFrames -= (float) Input::getDelta ();

		} else {

			this->skipFrames = 0.0f;

		}

		if (this->skipFrames < 150.0f && this->skipFrames > 0.0f) {

			if (Input::controllerUsed ()) {

				if (Input::buttonHeld (SDL_CONTROLLER_START)) {

					//Set player position
					player->setPosition (this->getPlayerX (), this->getPlayerY ());

					//Set camera position (with offset)
					Sprite::setCamera (this->getCamPosX (), this->getCamPosY ());

					//Replace arena
					*arena = new_Arena (this->nextArena);

					//Set game state
					*gameState = GameState::GAME;

					return true;

				}

			} else {

				if (Input::keyHeld (SDL_SCANCODE_RETURN)) {

					//Set player position
					player->setPosition (this->getPlayerX (), this->getPlayerY ());

					//Set camera position (with offset)
					Sprite::setCamera (this->getCamPosX (), this->getCamPosY ());

					//Replace arena
					*arena = new_Arena (this->nextArena);

					//Set game state
					*gameState = GameState::GAME;

					return true;

				}

			}

			if (this->skipFrames < 120.0f) {

				this->skipButtonSprite->setAlpha ((int) (this->skipFrames * 255 / 120));

			}

		}

	} 

	//Render tile
	this->current->tile->render (screen);

	//If dialogue is playing, do the calculations
	if (this->dialogue_playing) {

		//Display text box
		this->textBox.render (screen, 0.166f, 0.655f, 1.0f, NULL);

		//If dialogue timer is
		if (this->dialogue_timer > Input::getDelta ()) {

			this->font.getFont ()->drawBox (screen, Font::getRect_s (0.216f, 0.705f, 0.90133333333f, 0.25555555555f), this->current_text->text);

			this->dialogue_timer -= (float) Input::getDelta ();

		} else {

			//If there's no more tiles, end dialogue, otherwise, move to next
			if (this->current_text->next != NULL) {

				//Go to next text
				this->current_text = this->current_text->next;

				//Set timing
				this->dialogue_timer = this->current_text->time;

			} else {

				//End dialogue
				this->dialogue_playing = false;

			}

		}

	}

	//Render skip button
	this->skipButtonSprite->render (screen, 0.8f, 0.76f, 2.0f, NULL);

	//Return false
	return false;

}

void Cutscene::createTileList (CutTile *data, TileList **first, TileList **last) {

	*first = _new TileList (data);

	*last = *first;

}

void Cutscene::addTileList (CutTile *data, TileList **last) {

	struct TileList *prev = *last;

	*last = _new TileList (data);

	prev->next = *last;

}

void Cutscene::createTextList (char *text, float time, TextList **first, TextList **last) {

	*first = _new TextList (text, time);

	*last = *first;

}

void Cutscene::addTextList (char *text, float time, TextList **last) {

	struct TextList *prev = *last;

	*last = _new TextList (text, time);

	prev->next = *last;

}

float Cutscene::getPlayerX () {

	return this->playerX;

}

float Cutscene::getPlayerY () {

	return this->playerY;

}

float Cutscene::getCamPosX () {

	return (this->playerX - this->cameraOffsetX - 0.5f);

}

float Cutscene::getCamPosY () {

	return (this->playerY - this->cameraOffsetY - 0.5f);

}
