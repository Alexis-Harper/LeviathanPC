#pragma once

#include "GameState.h"

#include "CutTile.h"
#include "Audio.h"
#include "Arena.h"
#include "Player.h"

class Cutscene {

public:

	//Constructors and destructors
	Cutscene (const char *filename);
	~Cutscene ();

	//Renderers
	void render (GPU_Target *screen, Arena **arena, Player *player, GameState *gameState);

private:

	//Audio
	Audio::Audio *audio;

	//List struct
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

	//Get post-cutscene arena information
	float getPlayerX ();
	float getPlayerY ();
	float getCamPosX ();
	float getCamPosY ();

	//Next arena to go to
	char *nextArena;

	float playerX, playerY, cameraOffsetX, cameraOffsetY;

};

