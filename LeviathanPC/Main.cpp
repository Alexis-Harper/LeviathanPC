#include "stdafx.h"

#include "ErrorEnum.h"
#include "GameState.h"

#include <chrono>

#include "Input.h"
#include "Player.h"
#include "Arena.h"
#include "Audio.h"
#include "Exit.h"
#include "Health.h"
#include "Cutscene.h"
#include "CutEvent.h"
#include "Font.h"
#include "AmmoLabel.h"
#include "PauseMenu.h"
#include "MainMenu.h"

using namespace std;

constexpr chrono::nanoseconds timestep (16ms); //60 ticks per sec

int main(int argc, char *args[]) {

	#ifndef _DEBUG

	freopen ("debug.log", "w", stdout);

	#endif

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

	//Get screen dimentions 
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
	
	//Set name of window
	SDL_SetWindowTitle (SDL_GetWindowFromID (screen->context->windowID), "The Leviathan");

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

		cout << "[+] SDL: No joysticks connected.\n\n";

	} else {

		gameController = SDL_JoystickOpen (0);

		if (gameController == NULL) {

			cout << "[-] SDL: Controller failed to open.\n";

		} else {

			hapticFeedback = SDL_HapticOpenFromJoystick (gameController);

			if (hapticFeedback == NULL) {

				cout << "[+] SDL: Controller does not support haptic feedback.\n\n";

			} else {

				if (SDL_HapticRumbleInit (hapticFeedback) < 0) {

					cout << "[-] SDL: " << SDL_GetError ();

				} else {

					cout << "[+] SDL: Haptic feedback working.\n\n";

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

		activeArena = new_Arena (args[1]);
		
	} else {

		activeArena = new_Arena ("assets/arena/TestArena.json");

	}

	//Pause arena music
	activeArena->pause (1);

	//Create current cutscene
	Cutscene *currentCutscene = NULL;

	//Set up player
	Player player = Player ();

	Health health;
	AmmoLabel ammoLabel;

	//Set game state
	GameState gameState = HOME_MENU;
	float pauseButtonBuffer = 0.0f;

	struct Menus {

		//Menu font
		Font font = Font (GameFonts::MAIN_FONT, 32, NFont::Color (200, 200, 200, 250));

		//Menu buttons
		SpriteSheet buttons = SpriteSheet ((char*) "assets/menu/MainButtons.png", 1, 2);

		//Menu objects
		MainMenu mainMenu = MainMenu (&this->font, &this->buttons);
		PauseMenu pauseMenu = PauseMenu (&this->font, &this->buttons);

	} menus;

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

			//Every frame
			startTime = chrono::high_resolution_clock::now();

			Input::setDelta ((double) (chrono::duration_cast<chrono::duration<double, nano>>(deltaTime) / chrono::duration_cast<chrono::duration<double, nano>>(timestep))); //Set delta

			//Input
			Input::update ();

			//If pause button is pressed, pause or unpause
			if (Input::keyHeld (SDL_SCANCODE_ESCAPE) && pauseButtonBuffer == 0.0f) {

				if (gameState == GAME) {

					pauseButtonBuffer = 30.0f;

					gameState = PAUSED;

				} else if (gameState == PAUSED) {

					pauseButtonBuffer = 15.0f;

					gameState = GAME;
				}

			} else {

				if (pauseButtonBuffer > 0.0f) {

					if (pauseButtonBuffer <= Input::getDelta ()) {

						pauseButtonBuffer = 0.0f;

					} else {

						pauseButtonBuffer -= (float) Input::getDelta ();

					}

				}

			}

			//Update

			if (gameState == GameState::GAME) {

				//Update arena
				activeArena->update ();

				//cout << "Direction: " << Input::eightDirection () << "\n\n";

				//Update player
				player.update (activeArena); //Update player

				//Update game objects
				activeArena->updateGameObjects (GameObject::AIArgs (activeArena, &player, &health));

				//If in debug mode, allow for player hit button
				#ifdef _DEBUG

				if (Input::keyHeld (SDL_SCANCODE_U)) {

					player.damage (10, &health);

				}

				#endif

			} else if (gameState == GameState::PAUSED) {

				menus.pauseMenu.update (gameState, menus.mainMenu, activeArena, viewport.h, viewport.x);

			} else if (gameState == GameState::HOME_MENU) {

				menus.mainMenu.update (gameState, activeArena, viewport.h, viewport.x);

			}

			//Render

			//Clear screen
			GPU_Clear (screen);

			//Game and paused mode render
			if (gameState == GameState::GAME || gameState == GameState::PAUSED || gameState == GameState::HOME_MENU) {

				//Render things
				activeArena->render (screen);

				player.render (screen);

				activeArena->renderGameObjects (screen);

				//State specific things
				if (gameState == GameState::GAME) {

					//Display HUD if in game mode
					health.render (screen);
					ammoLabel.render (screen, player);

				} else if (gameState == GameState::PAUSED) {

					//If paused, render pause menu
					menus.pauseMenu.render (screen);

				} else if (gameState == GameState::HOME_MENU) {

					//If on main menu, render main menu
					menus.mainMenu.render (screen);

				}

			} else if (gameState = GameState::CUTSCENE) {

				//If cutscene is done, delete it
				if (currentCutscene->render (screen, &activeArena, &player, &gameState)) {

					delete currentCutscene;

					currentCutscene = NULL;

				}

			}

			//Display screen
			GPU_Flip (screen);

			//If the player is in game mode, check if they are in an exit or event area
			if (gameState == GameState::GAME) {

				//Test if player is exiting arena
				Exit::testForExit (&activeArena, &player);

				//Test if player is in event area
				CutEvent::testForEvent (&gameState, &activeArena, &currentCutscene, &player);

			}

		}

	}

	//Close program

	//Close arena if open
	if (activeArena != NULL) {

		delete activeArena;

	}

	if (currentCutscene != NULL) {

		delete currentCutscene;

	}

	SDL_JoystickClose (gameController);
	SDL_HapticClose (hapticFeedback);

	//Destroy window
	GPU_Quit ();

	//Quit SDL subsystems
	SDL_CloseAudio ();
	SDL_Quit ();

	return 0;

}
