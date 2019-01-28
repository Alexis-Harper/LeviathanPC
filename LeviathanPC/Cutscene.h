#pragma once

/**
 * Author:    Alexis Harper
 * Created:   12.11.2018
 *
 * Description: The Cutscene class contains the information within a cutscene
 *              and manages the rendering of it.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 **/

#include "GameState.h"

#include "CutTile.h"
#include "Audio.h"
#include "Arena.h"
#include "Player.h"
#include "Font.h"

class Cutscene {

public:

	//Constructors and destructors
	Cutscene (const char *filename);
	~Cutscene ();

	//Renderers
	bool render (GPU_Target *screen, Arena **arena, Player *player, GameState *gameState);

private:

	//Audio
	Audio::Audio *audio;

	//Skip button
	Sprite *skipButtonSprite;

	//Frame counter for skipping
	float skipFrames;

	//List struct (tiles)
	struct TileList {

		CutTile *tile;
		struct TileList *next;

		TileList (CutTile *tile) : tile (tile) { this->next = NULL; };

	};

	//Current timings
	float current_fade_in, current_stay_time, current_fade_out;

	//Tile list
	struct TileList *first_tile = NULL, *last_tile = NULL, *current = NULL;

	//List manipulators
	static void createTileList (CutTile *data, TileList **first, TileList **last);
	static void addTileList (CutTile *data, TileList **last);

	//Sprite for showing text
	Sprite textBox = Sprite ((char*) "assets/cutscenes/images/CutsceneTextBox.png");

	//Text font
	Font font = Font (GameFonts::MAIN_FONT, 32, NFont::Color (220, 220, 220, 250));

	//List struct (dialogue)
	struct TextList {

		char *text;
		float time;
		struct TextList *next;

		TextList (char *text, float time) : text (text), time (time) { this->next = NULL; };

	};

	//Current dialogue timing
	float dialogue_timer;
	bool dialogue_playing;

	//Text list
	struct TextList *first_text = NULL, *last_text = NULL, *current_text = NULL;

	//List manipulators
	static void createTextList (char *text, float time, TextList **first, TextList **last);
	static void addTextList (char *text, float time, TextList **last);

	//Get post-cutscene arena information
	float getPlayerX ();
	float getPlayerY ();
	float getCamPosX ();
	float getCamPosY ();

	//Next arena to go to
	char *nextArena;

	//Coords to be set when cutscene is done
	float playerX, playerY, cameraOffsetX, cameraOffsetY;

};

