#include "stdafx.h"
#include "Stats.h"

#include "ErrorEnum.h"

#include <fstream>

#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/writer.h>

using namespace std;
using namespace rapidjson;


Statistics::Statistics () 
{

}


Statistics::~Statistics () 
{

}


bool Statistics::load ()
{
	rapidjson::Document json;

	//Alert that save is loading
	cout << "[+] Loading stat file to read.\n";

	//File input pointer
	FILE* f;

	//Check if file exists
	if (f = fopen ("stat_data.sav", "rb"))
	{
		//Get file input
		char buf[65536];
		FileReadStream is = FileReadStream (f, buf, sizeof (buf));

		//Copy file to memory, exit if failed
		if (f == NULL) 
		{
			cout << "[-] Stat: Stat file failed to load for reading.\n";

			exit (ERROR_SAVE_LOAD_LOAD_FILE);
		}

		fclose (f); //Close file

		//Parse JSON file
		json.Parse (buf);

		//If JSON failed to load, give error
		if (!json.IsObject ()) 
		{
			cout << "[-] Stat: JSON file failed to parse.\n";

			exit (ERROR_STAT_LOAD_PARSE_JSON);
		}

		//Deal with version difference
		{
			const Value &version = json["Version"];

			size_t size = version.GetStringLength () + 1;
			char *buf = _new char[size];
			strcpy (buf, version.GetString ());

			//Check the version and make changes depending
			if (!strcmp (buf, "1.0.0 alpha"))
			{
				cout << "[+] Stat: Loading version 1.0.0 alpha save\n";
			}

			delete buf;
		}

		//Get stats from file
		this->kills = json["Kills"].GetUint64 ();
		this->deaths = json["Deaths"].GetUint64 ();
		this->damageTaken = json["DamageTaken"].GetUint64 ();
		this->damageDelt = json["DamageDelt"].GetUint64 ();
		this->distance = json["Distance"].GetDouble ();
		this->auraAttempts = json["AuraAttempts"].GetUint64 ();
		this->auraHits = json["AuraHits"].GetUint64 ();
		this->sprintDashes = json["SprintDashes"].GetUint64 ();

		return false;
	} 
	else 
	{
		//Create blank information
		this->kills = 0;
		this->deaths = 0;
		this->damageTaken = 0;
		this->damageDelt = 0;
		this->distance = 0.0;
		this->auraAttempts = 0;
		this->auraHits = 0;
		this->sprintDashes = 0;

		return true;
	}
}


void Statistics::save ()
{
	Document json;
	json.SetObject ();

	//Alert that arena is loading
	cout << "[+] Loading stats file to write.\n";

	//Write JSON
	{
		Document::AllocatorType &alloc = json.GetAllocator ();

		json.AddMember ("Version", Value ().SetString ("1.0.0 alpha"), alloc);

		json.AddMember ("Kills", Value ().SetUint64 (this->kills), alloc);
		json.AddMember ("Deaths", Value ().SetUint64 (this->deaths), alloc);
		json.AddMember ("DamageTaken", Value ().SetUint64 (this->damageTaken),
						alloc);
		json.AddMember ("DamageDelt", Value ().SetUint64 (this->damageDelt),
						alloc);
		json.AddMember ("Distance", Value ().SetDouble (this->distance), 
						alloc);
		json.AddMember ("AuraAttempts", Value ().SetUint64 (this->auraAttempts),
						alloc);
		json.AddMember ("AuraHits", Value ().SetUint64 (this->auraHits), 
						alloc);
		json.AddMember ("SprintDashes", Value ().SetUint64 (this->sprintDashes),
						alloc);
	}

	//File output pointer
	FILE* f;

	//See if file can be written to
	if (f = fopen ("stat_data.sav", "wb")) 
	{
		//Get file input
		char buf[65536];
		FileWriteStream os (f, buf, sizeof (buf));

		//Write JSON to file
		Writer<FileWriteStream> writer (os);
		json.Accept (writer);

		//TODO write data

		//Close file
		fclose (f);
	}
	else 
	{
		//Close file before printing error
		fclose (f);

		cout << "[-] Stat: Stat file failed to load for saving.\n";

		exit (ERROR_STAT_SAVE_LOAD_FILE);
	}

	return;
}


void Statistics::incrementKills () 
{
	this->kills++;

	return;
}


void Statistics::incrementDeaths () 
{
	this->deaths++;

	return;
}


void Statistics::incrementDamageTaken (unsigned int damage) 
{
	this->damageDelt += damage;

	return;
}


void Statistics::incrementDamageDelt (unsigned int damage) 
{
	this->damageTaken += damage;

	return;
}


void Statistics::incrementDistance (float vx, float vy) 
{
	//Add distance
	this->distance += sqrt (vx * vx + vy * vy);

	return;
}


void Statistics::auraAttempted () 
{
	this->auraAttempts++;

	return;
}


void Statistics::auraHit () 
{
	this->auraHits++;

	return;
}

void Statistics::sprintDashed ()
{
	this->sprintDashes++;
}
