#include "stdafx.h"
#include "Game.h"

using namespace std;


constexpr chrono::nanoseconds timestep (16ms); //60 ticks per sec


Game::Game () :
	window ("The Leviathan"),
	gameController (NULL),
	hapticFeedback (NULL),
	statObject (),
	activeArena (NULL),
	currentCutscene (NULL),
	player (),
	health (),
	ammoLabel (),
	gameState (HOME_MENU),
	pauseButtonBuffer (0.0f),
	exitBool (false),
	sdlEvent (),
	menus ()
{

}


Game::~Game ()
{
	//Close program

	//Close arena if open
	if (activeArena != NULL)
	{
		delete activeArena;
	}

	//Stop mem leak
	Arena::exit ();

	if (currentCutscene != NULL)
	{
		delete currentCutscene;
	}

	SDL_JoystickClose (gameController);
	SDL_HapticClose (hapticFeedback);

	//Destroy window
	GPU_Quit ();

	//Quit SDL subsystems
	SDL_CloseAudio ();
	SDL_Quit ();
}


void Game::init ()
{
	#ifdef _DEBUG

	_CrtSetDbgFlag (_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	#else

	freopen ("debug.log", "w", stdout);

	#endif

	//Initialize SDL Video
	if (SDL_Init (SDL_INIT_VIDEO) < 0)
	{
		cout << "[-] SDL: " << SDL_GetError () << "\n";

		exit (ERROR_SDL_INIT_VIDEO);
	}
	else
	{
		cout << "[+] SDL: Video initialized.\n";
	}

	//Initialize SDL Audio
	if (SDL_Init (SDL_INIT_AUDIO) < 0)
	{
		cout << "[-] SDL: " << SDL_GetError () << "\n";

		exit (ERROR_SDL_INIT_AUDIO);
	}
	else
	{
		cout << "[+] SDL: Audio initialized.\n";
	}

	//Initialize SDL Joystick
	if (SDL_Init (SDL_INIT_JOYSTICK) < 0)
	{
		cout << "[-] SDL: " << SDL_GetError () << "\n";

		exit (ERROR_SDL_INIT_JOYSTICK);
	}
	else
	{
		cout << "[+] SDL: Joystick initialized.\n";
	}

	if (SDL_Init (SDL_INIT_HAPTIC) < 0)
	{
		cout << "[-] SDL: " << SDL_GetError () << "\n";

		exit (ERROR_SDL_INIT_HAPTIC);
	}
	else
	{
		cout << "[+] SDL: Haptic controller feedback initialized.\n\n";
	}
}


int Game::run (int argc, char *args[])
{
	//Set up joystick
	{
		//Set up joystick
		SDL_Joystick *gameController = NULL;
		SDL_Haptic *hapticFeedback = NULL;

		if (SDL_NumJoysticks () < 1) 
		{
			cout << "[+] SDL: No joysticks connected.\n\n";
		} 
		else 
		{
			gameController = SDL_JoystickOpen (0);

			if (gameController == NULL) 
			{
				cout << "[-] SDL: Controller failed to open.\n";
			} 
			else 
			{
				hapticFeedback = SDL_HapticOpenFromJoystick (gameController);

				if (hapticFeedback == NULL) 
				{
					cout << "[+] SDL: Controller does not support haptic" 
						<< "feedback.\n\n";
				} 
				else 
				{
					if (SDL_HapticRumbleInit (hapticFeedback) < 0) 
					{
						cout << "[-] SDL: " << SDL_GetError ();
					} 
					else 
					{
						cout << "[+] SDL: Haptic feedback working.\n\n";

						Input::isHapticUsed (true);
						Input::setHapticFeedback (hapticFeedback);
					}
				}

				Input::isControllerUsed (true);
			}
		}
	}

	//Load save and statistics
	statObject.load ();

	//Initialize game
	Input::init ();
	Arena::init ();

	//Set up arena
	if (argc > 1) 
	{
		activeArena = new_Arena (args[1]);
	} 
	else 
	{
		activeArena = new_Arena ("assets/arena/TestArena.json");
	}

	//Pause arena music
	activeArena->pause (1);

	/*
	Get time right after initialization (initial time before first start time 
	reset later on)
	*/
	auto startTime = chrono::high_resolution_clock::now (); 

	while (!exitBool)
	{
		//Calculates delta (time since last frame)
		auto deltaTime = chrono::high_resolution_clock::now () - startTime;

		processEvents ();

		//Limit FPS to 60 Hz
		if (chrono::duration_cast<chrono::nanoseconds>(deltaTime) >= timestep)
		{
			//Every frame
			startTime = chrono::high_resolution_clock::now ();

			Input::setDelta (
				(double) (chrono::duration_cast<chrono::duration<double, nano>>
				(deltaTime) / chrono::duration_cast<chrono::duration<double,
				nano>>(timestep))); //Set delta

			//Input
			Input::update ();

			processPause ();
			update ();
			render (window.getTarget ());
		}
	}

	return 0;
}


void Game::processEvents ()
{
	while (SDL_PollEvent (&sdlEvent))
	{
		switch (sdlEvent.type)
		{
		case SDL_QUIT:

			exitBool = true;

			break;

		case SDL_WINDOWEVENT:

			if (sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED)
			{
				//Resize viewport to fit the aspect ratio
				window.resize (sdlEvent.window.data1, sdlEvent.window.data2);
			}

			break;

		case SDL_JOYAXISMOTION:

			if (sdlEvent.jaxis.which == 0)
			{
				switch (sdlEvent.jaxis.axis)
				{
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
			cout << "Button Pressed: " << (int) sdlEvent.jbutton.button
				<< "\n";

			break;

		case SDL_JOYBUTTONUP:

			Input::joyButtonPressed (sdlEvent.jbutton.button, false);

			break;

		case SDL_JOYDEVICEADDED:

			cout << "[+] SDL: Joystick device " << sdlEvent.jdevice.which
				<< " added.\n";

			if (gameController == NULL)
			{
				gameController = SDL_JoystickOpen (0);

				if (gameController == NULL)
				{
					cout << "[-] SDL: Controller failed to open.\n";
				}
				else
				{
					Input::isControllerUsed (true);
				}
			}

			break;

		case SDL_JOYDEVICEREMOVED:

			cout << "[+] SDL: Joystick device " << sdlEvent.jdevice.which
				<< " removed.\n";

			if (sdlEvent.jdevice.which == 0)
			{
				SDL_JoystickClose (gameController);

				gameController = NULL;

				Input::isControllerUsed (false);
			}

			break;
		}
	}

	return;
}


void Game::processPause ()
{
	//If pause button is pressed, pause or unpause
	if (Input::keyHeld (SDL_SCANCODE_ESCAPE) &&
		pauseButtonBuffer == 0.0f)
	{
		if (gameState == GAME)
		{
			pauseButtonBuffer = 30.0f;

			gameState = PAUSED;
		}
		else if (gameState == PAUSED)
		{
			pauseButtonBuffer = 15.0f;

			gameState = GAME;
		}
	}
	else
	{
		if (pauseButtonBuffer > 0.0f)
		{
			if (pauseButtonBuffer <= Input::getDelta ())
			{
				pauseButtonBuffer = 0.0f;
			}
			else
			{
				pauseButtonBuffer -= (float) Input::getDelta ();
			}
		}
	}

	return;
}


void Game::update ()
{
	if (gameState == GameState::GAME)
	{
		//Update arena
		activeArena->update ();

		//cout << "Direction: " << Input::eightDirection () << "\n\n";

		//Update player
		player.update (activeArena, statObject); //Update player

		//Update game objects
		activeArena->updateGameObjects (
			GameObject::AIArgs (activeArena, &player, &health));

		//If in debug mode, allow for player hit button
		#ifdef _DEBUG

		if (Input::keyHeld (SDL_SCANCODE_U))
		{
			player.damage (10, &health);
		}

		#endif
	}
	else if (gameState == GameState::PAUSED)
	{
		menus.pauseMenu.update (gameState, menus.mainMenu, activeArena,
								window.getViewport ().h, 
								window.getViewport ().x);
	}
	else if (gameState == GameState::HOME_MENU)
	{
		menus.mainMenu.update (gameState, activeArena, window.getViewport ().h,
							   window.getViewport ().x);
	}

	/*
	If the player is in game mode, check if they are in an exit or
	event area
	*/
	if (gameState == GameState::GAME)
	{
		//Test if player is exiting arena
		Exit::testForExit (activeArena, player);

		//Test if player is in event area
		CutEvent::testForEvent (gameState, activeArena,
								currentCutscene, player);
	}

	return;
}


void Game::render (GPU_Target * screen)
{
	//Clear screen
	GPU_Clear (screen);

	//Game and paused mode render
	if (gameState == GameState::GAME || gameState == GameState::PAUSED
		|| gameState == GameState::HOME_MENU)
	{
		//Render things
		activeArena->render (screen);

		player.render (screen);

		activeArena->renderGameObjects (screen);

		//State specific things
		if (gameState == GameState::GAME)
		{
			//Display HUD if in game mode
			health.render (screen);
			ammoLabel.render (screen, player);
		}
		else if (gameState == GameState::PAUSED)
		{
			//If paused, render pause menu
			menus.pauseMenu.render (screen);
		}
		else if (gameState == GameState::HOME_MENU)
		{
			//If on main menu, render main menu
			menus.mainMenu.render (screen);
		}
	}
	else if (gameState = GameState::CUTSCENE)
	{
		//If cutscene is done, delete it
		if (currentCutscene->render (screen, activeArena, player,
			gameState))
		{
			delete currentCutscene;

			currentCutscene = NULL;
		}
	}

	//Display screen
	GPU_Flip (screen);

	return;
}
