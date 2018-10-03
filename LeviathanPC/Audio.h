#pragma once

namespace Audio {

	class Audio {

	public:

		Audio ();
		Audio (const char *filename, const char *channelName);
		~Audio ();

		void reQueue ();

		void pause (int pause);

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
		Music (const char* filename);
		~Music ();

		void render ();

		void pause (int pause);

	private:

		Audio *audio = NULL;

	};

	class Effect {

	public:

		Effect ();
		Effect (const char* filename);
		~Effect ();

		void playEffect ();

	private:

		Audio *audio = NULL;

	};

};
