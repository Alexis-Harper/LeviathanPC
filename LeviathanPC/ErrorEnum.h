#pragma once

/**
 * Author:    Alexis Harper
 * Created:   17.09.2018
 *
 * Description: Contains exit error codes for easier exit function readability 
 *             and easier checking of error values.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 **/

enum ERROR {

	ERROR_SDL_INIT_VIDEO = 2,
	ERROR_SDL_INIT_AUDIO,
	ERROR_SDL_INIT_JOYSTICK,
	ERROR_SDL_INIT_HAPTIC,
	ERROR_SDL_WINDOW_FAILED_TO_LOAD,
	ERROR_SDL_JOYSTICK_LOAD,
	ERROR_SDL_AUDIO_WAV_LOAD,
	ERROR_GPU_TEXTURE_LOAD,
	ERROR_GPU_SHADER_LOAD_V,
	ERROR_GPU_SHADER_LOAD_F,
	ERROR_GPU_SHADER_LINK,
	ERROR_ARENA_LOAD_FILE,
	ERROR_ARENA_PARSE_JSON,
	ERROR_CUTSCENE_LOAD_FILE,
	ERROR_CUTSCENE_PARSE_JSON

};
