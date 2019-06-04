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

//Audio class namespace
namespace Audio 
{
	//Base Audio class
	class Audio 
	{
	public:

		Audio ();
		Audio (const char *filename, const char *channelName);
		~Audio ();

		//Re-queue audio
		void reQueue ();

		//Pause audio
		void pause (int pause);

		//Get audio device ID
		SDL_AudioDeviceID getDeviceID ();

	private:

		//WAV data
		Uint32 wav_length;
		Uint8 *wav_buffer = NULL;
		SDL_AudioSpec wav_spec;
		SDL_AudioDeviceID device_id;
		int success;
	};

	//Audio class specialized for music
	class Music 
	{
	public:

		Music ();
		Music (const char* filename);
		~Music ();

		//Render music (re-queues automatically to repeat)
		void render ();

		//Pause music
		void pause (int pause);

	private:

		//Base audio object
		Audio *audio = NULL;
	};

	//Audio class made for sound effects
	class Effect 
	{
	public:

		Effect ();
		Effect (const char* filename);
		~Effect ();

		//Play sound effect
		void playEffect ();

	private:

		//Base audio object
		Audio *audio = NULL;
	};
};
