#pragma once

namespace Audio {

	class Audio {

	public:

		Audio ();
		Audio (char*, char*);
		~Audio ();

		void reQueue ();

		void pause (int);

		SDL_AudioDeviceID getDeviceID ();

	private:

		Uint32 wav_length;
		Uint8 *wav_buffer = NULL;
		SDL_AudioSpec wav_spec;
		SDL_AudioDeviceID device_id;
		int success;

	};

	class Music {

	public:

		Music ();
		Music (char*);
		~Music ();

		void render ();

		void pause (int);

	private:

		Audio *audio = NULL;

	};

	class Effect {

	public:

		Effect ();
		Effect (char*);
		~Effect ();

	private:



	};

};
