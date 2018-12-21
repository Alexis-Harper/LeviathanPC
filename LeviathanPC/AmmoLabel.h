#pragma once

/**
 * Author:    Alexis Harper
 * Created:   20.12.2018
 *
 * Description: The Player class contains data on the current player, as well
 *              as doing the rendering.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 **/

#include "Font.h"
#include "Player.h"

class AmmoLabel {

public:

	AmmoLabel ();
	~AmmoLabel ();

	void render (GPU_Target *screen, Player &player);

private:

	Font *font;

};

