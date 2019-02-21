#include "stdafx.h"
#include "Audio.h"

#include "ErrorEnum.h"

#include "SDL_audio.h"

namespace Audio {

	namespace {

		

	}

	Audio::Audio () {

		//Default constructor

	}

	Audio::Audio (const char *filename, const char *channelName) {

		if (SDL_LoadWAV (filename, &this->wav_spec, &this->wav_buffer, &this->wav_length) == NULL) {

			std::cout << "[-] SDL: " << SDL_GetError () << "\n";

			exit (ERROR_SDL_AUDIO_WAV_LOAD);

		}

		this->device_id = SDL_OpenAudioDevice (channelName, 0, &this->wav_spec, NULL, 0);

		this->success = SDL_QueueAudio (this->device_id, this->wav_buffer, this->wav_length);

	}

	Audio::~Audio () {

		SDL_ClearQueuedAudio (this->device_id);
		SDL_CloseAudioDevice (this->device_id);
		SDL_FreeWAV (this->wav_buffer);

	}

	void Audio::reQueue () {

		SDL_ClearQueuedAudio (this->device_id);

		this->success = SDL_QueueAudio (this->device_id, this->wav_buffer, this->wav_length);

	}

	void Audio::pause (int on) {

		SDL_PauseAudioDevice (this->device_id, on);

	}

	SDL_AudioDeviceID Audio::getDeviceID () {

		return this->device_id;

	}

	Music::Music () {

		//Default constructor

	}

	Music::Music (const char *filename) {

		this->audio = _new Audio (filename, NULL);

	}

	Music::~Music () {

		delete this->audio;

	}

	void Music::render () {

		if (SDL_GetQueuedAudioSize (this->audio->getDeviceID()) <= 100000) {

			this->audio->reQueue ();
			this->audio->pause (0);

		}

	}

	void Music::pause (int pause) {

		this->audio->pause (pause);

	}

	Effect::Effect () {

		//Default constructor

	}

	Effect::Effect (const char* filename) {

		this->audio = _new Audio (filename, NULL);

	}

	Effect::~Effect () {

		delete this->audio;

	}

	void Effect::playEffect () {

		this->audio->reQueue ();
		this->audio->pause (0);

	}

};