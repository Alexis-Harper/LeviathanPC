#include "stdafx.h"

#include "ErrorEnum.h"

#include <chrono>

#include "Input.h"
#include "Player.h"
#include "Arena.h"
#include "Audio.h"
#include "Exit.h"

#include "Health.h"

using namespace std;

constexpr chrono::nanoseconds timestep (16ms); //60 ticks per sec

enum GameState {

	HOME_MENU,
	GAME,
	PAUSED

} gameState;

int main(int argc, char *args[]) {

	//Window pointer
	SDL_Window* window = NULL;

	//Initialize SDL Video
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {

		cout << "[-] SDL: " << SDL_GetError() << "\n";

		return ERROR_SDL_INIT_VIDEO;

	} else {

		cout << "[+] SDL: Video initialized.\n";

	}

	//Initialize SDL Audio
	if (SDL_Init (SDL_INIT_AUDIO) < 0) {

		cout << "[-] SDL: " << SDL_GetError () << "\n";

		return ERROR_SDL_INIT_AUDIO;

	} else {

		cout << "[+] SDL: Audio initialized.\n";

	}

	//Initialize SDL Joystick
	if (SDL_Init (SDL_INIT_JOYSTICK) < 0) {

		cout << "[-] SDL: " << SDL_GetError () << "\n";

		return ERROR_SDL_INIT_JOYSTICK;

	} else {

		cout << "[+] SDL: Joystick initialized.\n";

	}

	if (SDL_Init (SDL_INIT_HAPTIC) < 0) {

		cout << "[-] SDL: " << SDL_GetError () << "\n";

		return ERROR_SDL_INIT_HAPTIC;

	} else {

		cout << "[+] SDL: Haptic controller feedback initialized.\n\n";

	}

	//Get SDL 
	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);

	int w = displayMode.w; //Get monitor dimentions in two variables
	int h = displayMode.h;

	int windowResX, windowResY;

	//Set dimentions of window to max sandard size for widescreen (I wrote this in Java and then recreated all the variables with the same name before this and copied and pasted. I love simiar programming languages)
	if (h < 240 && w < 256) {

		//144p 4:3
		windowResX = 192;
		windowResY = 144;

	} else if (h < 240) {

		//144p 16:9
		windowResX = 256;
		windowResY = 144;

	} else if (h < 360 && w < 426) {

		//240p 4:3
		windowResX = 320;
		windowResY = 240;

	} else if (h < 360) {

		//240p 16:9
		windowResX = 426;
		windowResY = 240;

	} else if (h < 480 && w < 640) {

		//360p 4:3
		windowResX = 480;
		windowResY = 360;

	} else if (h < 480) {

		//360p 16:9
		windowResX = 640;
		windowResY = 360;

	} else if (h < 720 && w < 854) {

		//480p 4:3
		windowResX = 640;
		windowResY = 480;

	} else if (h < 720) {

		//480p 16:9
		windowResX = 854;
		windowResY = 480;

	} else if (h < 1080) {

		//720p 16:9
		windowResX = 1280;
		windowResY = 720;

	} else if (h < 2160) {

		//1080p 16:9
		windowResX = 1920;
		windowResY = 1080;

	} else {

		//4K
		windowResX = 3840;
		windowResY = 2160;

	}

	//Tell us if any errors happen at all
	GPU_SetDebugLevel (GPU_DEBUG_LEVEL_MAX);

	GPU_Target* screen = GPU_Init (windowResX, windowResY, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	
	if (screen == NULL) {

		cout << "[-] GPU: " << SDL_GetError () << "\n";

		return ERROR_SDL_WINDOW_FAILED_TO_LOAD;

	}

	//Set up viewport
	GPU_Rect viewport;

	viewport.w = windowResY * 1.33333333333f;
	viewport.h = (float) windowResY;

	viewport.x = (windowResX - viewport.w) / 2.0f;
	viewport.y = 0.0f;

	GPU_SetViewport (screen, viewport);

	//Set up sprites
	Sprite::updateScreenDimentions (viewport.w, viewport.h);
	Sprite::setCamera (0.0f, 0.0f);

	//Set up joystick
	SDL_Joystick *gameController = NULL;
	SDL_Haptic *hapticFeedback = NULL;

	if (SDL_NumJoysticks () < 1) {

		cout << "[+] SDL: No joysticks connected.\n";

	} else {

		gameController = SDL_JoystickOpen (0);

		if (gameController == NULL) {

			cout << "[-] SDL: Controller failed to open.\n";

		} else {

			hapticFeedback = SDL_HapticOpenFromJoystick (gameController);

			if (hapticFeedback == NULL) {

				cout << "[+] SDL: Controller does not support haptic feedback.\n";

			} else {

				if (SDL_HapticRumbleInit (hapticFeedback) < 0) {

					cout << "[-] SDL: " << SDL_GetError ();

				} else {

					cout << "[+] SDL: Haptic feedback working.\n";

					Input::isHapticUsed (true);
					Input::setHapticFeedback (hapticFeedback);

				}

			}

			Input::isControllerUsed (true);

		}

	}

	Input::init ();
	Arena::init ();

	//Set up arena
	Arena *activeArena;

	if (argc > 1) {

		activeArena = new Arena (args[1]);
		
	} else {

		activeArena = new Arena ((const char*) "assets/arena/TestArena.json");

	}

	//Set up player
	Player player = Player ();

	Health health;

	//SDL Events
	bool exit = false;
	SDL_Event sdlEvent;

	auto startTime = chrono::high_resolution_clock::now (); //Get time right after initialization (initial time before first start time reset later on)

	while (!exit) {

		auto deltaTime = chrono::high_resolution_clock::now () - startTime; //Calculates delta (time since last frame)

		while (SDL_PollEvent (&sdlEvent)) {

			switch (sdlEvent.type) {

			case SDL_QUIT:

				exit = true;

				break;

			case SDL_WINDOWEVENT:

				if (sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED) {

					//Resize viewport to fit the aspect ratio
					windowResX = sdlEvent.window.data1;
					windowResY = sdlEvent.window.data2;

					viewport.w = windowResY * 1.33333333333f;
					viewport.h = (float) windowResY;

					viewport.x = (windowResX - viewport.w) / 2.0f;
					viewport.y = 0.0f;

					GPU_SetViewport (screen, viewport);

					Sprite::updateScreenDimentions (viewport.w, viewport.h);

				}

				break;

			case SDL_JOYAXISMOTION:

				if (sdlEvent.jaxis.which == 0) {

					switch (sdlEvent.jaxis.axis) {

					case 0: 

						Input::joyAxis0X (sdlEvent.jaxis.value / 32767.0f);

						break;

					case 1:

						Input::joyAxis0Y (sdlEvent.jaxis.value / 32767.0f);

						break;

					case 3:

						Input::joyAxis1X (sdlEvent.jaxis.value / 32757.0f);

						break;

					case 4:

						Input::joyAxis1Y (sdlEvent.jaxis.value / 32767.0f);

						break;

					}

				}

				break;

			case SDL_JOYBUTTONDOWN:

				Input::joyButtonPressed (sdlEvent.jbutton.button, true);
				cout << "Button Pressed: " << (int) sdlEvent.jbutton.button << "\n";

				break;

			case SDL_JOYBUTTONUP:

				Input::joyButtonPressed (sdlEvent.jbutton.button, false);

				break;

			case SDL_JOYDEVICEADDED:

				cout << "[+] SDL: Joystick device " << sdlEvent.jdevice.which << " added.\n";

				if (gameController == NULL) {

					gameController = SDL_JoystickOpen (0);

					if (gameController == NULL) {

						cout << "[-] SDL: Controller failed to open.\n";

					} else {

						Input::isControllerUsed (true);

					}

				}

				break;

			case SDL_JOYDEVICEREMOVED:

				cout << "[+] SDL: Joystick device " << sdlEvent.jdevice.which << " removed.\n";

				if (sdlEvent.jdevice.which == 0) {

					SDL_JoystickClose (gameController);

					gameController = NULL;

					Input::isControllerUsed (false);

				}

				break;

			}

		}

		//Limit FPS to 60 Hz
		if (chrono::duration_cast<chrono::nanoseconds>(deltaTime) >= timestep) {

			startTime = chrono::high_resolution_clock::now();

			Input::setDelta ((double) (chrono::duration_cast<chrono::duration<double, nano>>(deltaTime) / chrono::duration_cast<chrono::duration<double, nano>>(timestep))); //Set delta

			//Input
			Input::update ();

			activeArena->update ();

			//Update

			//cout << "Direction: " << Input::eightDirection () << "\n\n";

			player.eightDirection (activeArena->canMove (player.getHixbox ())); //Get if player can wall

			player.update (activeArena);

			#ifdef _DEBUG

			if (Input::keyHeld (SDL_SCANCODE_U)) {

				player.damage (10, &health);

			}

			#endif

			//Render

			GPU_Clear (screen);

			//Render things
			activeArena->render (screen);

			player.render (screen);

			health.render (screen);

			GPU_Flip (screen);

			//Test if player is exiting arena
			Exit::testForExit (&activeArena, &player);

		}

	}

	//Close program
	delete activeArena;

	SDL_JoystickClose (gameController);
	SDL_HapticClose (hapticFeedback);

	//Destroy window
	GPU_Quit ();

	//Quit SDL subsystems
	SDL_CloseAudio ();
	SDL_Quit ();

	return 0;

}
