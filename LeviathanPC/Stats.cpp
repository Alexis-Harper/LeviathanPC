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

		//Get stats from file
		this->kills = json["Kills"].GetInt ();

		return false;
	} 
	else 
	{
		//Create blank information
		this->kills = 0;
		this->deaths = 0;
		this->distance = 0.0f;
		this->auraAttempts = 0;
		this->auraHits = 0;

		return true;
	}
}


void Statistics::save ()
{
	rapidjson::Document json;

	//Alert that arena is loading
	cout << "[+] Loading stats file to write.\n";

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
