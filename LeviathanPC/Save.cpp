#include "stdafx.h"
#include "Save.h"

#include "ErrorEnum.h"

#include <fstream>

#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/writer.h>

using namespace std;
using namespace rapidjson;


Save::Save () 
{

}


Save::~Save ()
{

}


bool Save::load () 
{
	rapidjson::Document json;

	//Alert that save file is loading to read
	cout << "[+] Loading save file to read.\n";

	//File input pointer
	FILE* f;

	//Check if file exists
	if (f = fopen ("save_data.sav", "rb")) 
	{
		//Get file input
		char buf[65536];
		FileReadStream is = FileReadStream (f, buf, sizeof (buf));

		//Copy file to memory, exit if failed
		if (f == NULL)
		{
			cout << "[-] Save: Save file failed to load for reading.\n";

			exit (ERROR_SAVE_LOAD_LOAD_FILE);
		}

		fclose (f); //Close file

		//Parse JSON file
		json.Parse (buf);

		//If JSON failed to load, give error
		if (!json.IsObject ()) 
		{
			cout << "[-] Save: JSON file failed to parse.\n";

			exit (ERROR_SAVE_LOAD_PARSE_JSON);
		}

		return false;
	} 
	else 
	{
		fclose (f);

		return true;
	}
}

void Save::save () 
{
	rapidjson::Document json;

	//Alert that save file is loading to write
	cout << "[+] Loading save file to write.\n";

	//File output pointer
	FILE* f;
	
	//See if file can be written to
	if (f = fopen ("save_data.sav", "wb")) 
	{
		//Get file input
		char buf[65536];
		FileWriteStream os (f, buf, sizeof (buf));

		//Write JSON to file
		Writer<FileWriteStream> writer (os);
		json.Accept (writer);

		//Close file
		fclose (f);
	} 
	else 
	{
		//Close file before printing error
		fclose (f);

		cout << "[-] Save: Save file failed to load for saving.\n";

		exit (ERROR_SAVE_SAVE_LOAD_FILE);
	}

	return;
}


SaveData::SaveData (const char *arenaFileame) :
	arenaFilename (arenaFilename)
{
	//Constructor
}


SaveData::~SaveData () 
{
	delete[] arenaFilename;
}
