#include "stdafx.h"
#include "Stats.h"

#include "ErrorEnum.h"

#include <fstream>

#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/writer.h>

using namespace std;
using namespace rapidjson;

Statistics::Statistics () {



}

Statistics::~Statistics () {



}


bool Statistics::load () {

	//Alert that save is loading
	cout << "[+] Loading save file to read.\n";

	//File input pointer
	FILE* f;

	//Check if file exists
	if (f = fopen ("save_data.sav", "rb")) {

		//Get file input
		char buf[65536];
		FileReadStream is = FileReadStream (f, buf, sizeof (buf));

		//Copy file to memory, exit if failed
		if (f == NULL) {

			cout << "[-] Save: Save file failed to load for reading.\n";

			exit (ERROR_SAVE_LOAD_LOAD_FILE);

		}

		fclose (f); //Close file

		//Parse JSON file
		this->json.Parse (buf);

		//If JSON failed to load, give error
		if (!this->json.IsObject ()) {

			cout << "[-] Save: JSON file failed to parse.\n";

			exit (ERROR_SAVE_LOAD_PARSE_JSON);

		}

		return false;

	} else {

		fclose (f);
		return true;

	}

}

void Statistics::save () {

	//Alert that arena is loading
	cout << "[+] Loading save file to write.\n";

	//File output pointer
	FILE* f;

	//See if file can be written to
	if (f = fopen ("save_data.sav", "wb")) {

		//Get file input
		char buf[65536];
		FileWriteStream os (f, buf, sizeof (buf));

		//Write JSON to file
		Writer<FileWriteStream> writer (os);
		this->json.Accept (writer);

		//Close file
		fclose (f);

	} else {

		//Close file before printing error
		fclose (f);

		cout << "[-] Save: Save file failed to load for saving.\n";

		exit (ERROR_SAVE_SAVE_LOAD_FILE);

	}

}
