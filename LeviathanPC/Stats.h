#pragma once

/**
 * Author:    Alexis Harper
 * Created:   25.02.2019
 *
 * Description: The Statistics class handles values relating to the statistics
 *              of the player in the game, such as the distance traveled, the
 *              number of deaths, the number of enemy/boss kills, etc. which
 *              will be used for leveling up. It may be player readable at
 *              some point in the future.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 **/

#include <rapidjson/document.h>

class Statistics {

public:

	Statistics ();
	~Statistics ();

	bool load ();
	void save ();

private:

	rapidjson::Document json;

};
