#include "stdafx.h"
#include "Window.h"

#include "ErrorEnum.h"

#include "Sprite.h"

using namespace std;


Window::Window (const char * windowName)
{
	//Get screen dimentions 
	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode (0, &displayMode);

	int w = displayMode.w; //Get monitor dimentions in two variables
	int h = displayMode.h;

	//Set dimentions of window to max sandard size for widescreen (I wrote this in Java and then recreated all the variables with the same name before this and copied and pasted. I love simiar programming languages)
	if (h < 240 && w < 256)
	{
		//144p 4:3
		windowResX = 192;
		windowResY = 144;
	}
	else if (h < 240)
	{
		//144p 16:9
		windowResX = 256;
		windowResY = 144;
	}
	else if (h < 360 && w < 426)
	{
		//240p 4:3
		windowResX = 320;
		windowResY = 240;
	}
	else if (h < 360)
	{
		//240p 16:9
		windowResX = 426;
		windowResY = 240;
	}
	else if (h < 480 && w < 640)
	{
		//360p 4:3
		windowResX = 480;
		windowResY = 360;
	}
	else if (h < 480)
	{
		//360p 16:9
		windowResX = 640;
		windowResY = 360;
	}
	else if (h < 720 && w < 854)
	{
		//480p 4:3
		windowResX = 640;
		windowResY = 480;
	}
	else if (h < 720)
	{
		//480p 16:9
		windowResX = 854;
		windowResY = 480;
	}
	else if (h < 1080)
	{
		//720p 16:9
		windowResX = 1280;
		windowResY = 720;
	}
	else if (h < 2160)
	{
		//1080p 16:9
		windowResX = 1920;
		windowResY = 1080;
	}
	else
	{
		//4K
		windowResX = 3840;
		windowResY = 2160;
	}

	//Tell us if any errors happen at all
	GPU_SetDebugLevel (GPU_DEBUG_LEVEL_MAX);

	screen = GPU_Init (windowResX, windowResY, 
					   SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	if (screen == NULL)
	{
		cout << "[-] GPU: " << SDL_GetError () << "\n";

		exit (ERROR_SDL_WINDOW_FAILED_TO_LOAD);
	}

	//Set name of window
	SDL_SetWindowTitle (SDL_GetWindowFromID (screen->context->windowID), 
						windowName);

	//Set up viewport
	viewport.w = windowResY * 1.33333333333f;
	viewport.h = (float) windowResY;

	viewport.x = (windowResX - viewport.w) / 2.0f;
	viewport.y = 0.0f;

	GPU_SetViewport (screen, viewport);

	//Set up sprites
	Sprite::updateScreenDimentions (viewport.w, viewport.h);
	Sprite::setCamera (0.0f, 0.0f);
}


Window::~Window ()
{

}


void Window::resize (int x, int y)
{
	//Resize viewport to fit the aspect ratio
	windowResX = x;
	windowResY = y;

	viewport.w = windowResY * 1.33333333333f;
	viewport.h = (float) windowResY;

	viewport.x = (windowResX - viewport.w) / 2.0f;
	viewport.y = 0.0f;

	GPU_SetViewport (screen, viewport);

	Sprite::updateScreenDimentions (viewport.w, viewport.h);
}


GPU_Target* Window::getTarget ()
{
	return this->screen;
}

GPU_Rect& Window::getViewport ()
{
	return this->viewport;
}
