#include "stdafx.h"
#include "Audio.h"

#include "ErrorEnum.h"

#include "SDL_audio.h"


Audio::Audio::Audio () 
{
	//Default constructor
}


Audio::Audio::Audio (const char *filename, const char *channelName)
{
	if (SDL_LoadWAV (filename, &this->wav_spec, &this->wav_buffer,
		&this->wav_length) == NULL)
	{
		std::cout << "[-] SDL: " << SDL_GetError () << "\n";

		exit (ERROR_SDL_AUDIO_WAV_LOAD);
	}

	this->device_id = SDL_OpenAudioDevice (channelName, 0, &this->wav_spec,
											NULL, 0);

	this->success = SDL_QueueAudio (this->device_id, this->wav_buffer, 
									this->wav_length);
}


Audio::Audio::~Audio ()
{
	SDL_ClearQueuedAudio (this->device_id);
	SDL_CloseAudioDevice (this->device_id);
	SDL_FreeWAV (this->wav_buffer);
}


void Audio::Audio::reQueue ()
{
	SDL_ClearQueuedAudio (this->device_id);

	this->success = SDL_QueueAudio (this->device_id, this->wav_buffer, this->wav_length);

	return;
}


void Audio::Audio::pause (int on)
{
	SDL_PauseAudioDevice (this->device_id, on);

	return;
}


SDL_AudioDeviceID Audio::Audio::getDeviceID ()
{
	return this->device_id;
}


Audio::Music::Music ()
{
	//Default constructor
}


Audio::Music::Music (const char *filename)
{
	this->audio = _new Audio (filename, NULL);
}


Audio::Music::~Music ()
{
	delete this->audio;
}


void Audio::Music::render ()
{
	if (SDL_GetQueuedAudioSize (this->audio->getDeviceID()) <= 100000) 
	{
		this->audio->reQueue ();
		this->audio->pause (0);
	}

	return;
}


void Audio::Music::pause (int pause)
{
	this->audio->pause (pause);

	return;
}


Audio::Effect::Effect ()
{
	//Default constructor
}


Audio::Effect::Effect (const char* filename)
{
	this->audio = _new Audio (filename, NULL);
}


Audio::Effect::~Effect ()
{
	delete this->audio;
}


void Audio::Effect::playEffect ()
{
	this->audio->reQueue ();
	this->audio->pause (0);

	return;
}
