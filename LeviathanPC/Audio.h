#pragma once

namespace Audio {

	class Audio {

	public:

		Audio ();
		Audio (char*, char*);
		~Audio ();

		void pause (int);

	private:

		Uint32 wav_length;
		Uint8 *wav_buffer;
		SDL_AudioSpec wav_spec;
		SDL_AudioDeviceID device_id;
		int success;

	};

	class Music {

	public:

		Music ();
		Music (char*);
		~Music ();

	private:



	};

	class Effect {

	public:

		Effect ();
		Effect (char*);
		~Effect ();

	private:



	};

};
