#pragma once

/**
 * Author:    Alexis Harper
 * Created:   16.09.2018
 *
 * Description: Audio.h contains classes that handle SDL audio abstractions. 
 *              Audio handles basic audio. Music handles more advanced audio
 *              that can loop. Effect is just a further abstraction of Audio
 *              with almost nothing more.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 **/

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
