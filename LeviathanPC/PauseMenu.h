#pragma once

/**
 * Author:    Alexis Harper
 * Created:   22.1.2019
 *
 * Description: A class that controls a pause menu.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 **/

#include "Font.h"

class PauseMenu {

public:

	PauseMenu ();
	~PauseMenu ();

	void render (GPU_Target *screen);

private:

	Font *font;

};
