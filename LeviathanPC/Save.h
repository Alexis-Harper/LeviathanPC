#pragma once

/**
 * Author:    Alexis Harper
 * Created:   25.02.2019
 *
 * Description: The Save class creates an object that manages JSON saves
 *              including the loading and saving of the file.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 **/

#include <rapidjson/document.h>

class Save {

public:

	Save ();
	~Save ();

	bool load ();
	void save ();

private:

	rapidjson::Document json;

};
