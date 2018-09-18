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

	Audio::Audio (char *filename, char *channelName) {

		if (SDL_LoadWAV (filename, &this->wav_spec, &this->wav_buffer, &this->wav_length) == NULL) {

			std::cout << "[-] SDL: " << SDL_GetError () << "\n";

			exit (ERROR_SDL_AUDIO_WAV_LOAD);

		}

		this->device_id = SDL_OpenAudioDevice (channelName, 0, &this->wav_spec, NULL, 0);

		this->success = SDL_QueueAudio (this->device_id, this->wav_buffer, this->wav_length);


	}

	Audio::~Audio () {

		SDL_CloseAudioDevice (this->device_id);
		SDL_FreeWAV (this->wav_buffer);

	}

	void Audio::pause (int on) {

		SDL_PauseAudioDevice (this->device_id, on);

	}

	Music::Music () {

		//Default constructor

	}

	Music::Music (char *filename) {



	}

	Music::~Music () {



	}

	Effect::Effect () {

		//Default constructor

	}

	Effect::Effect (char* filename) {



	}

	Effect::~Effect () {



	}

};