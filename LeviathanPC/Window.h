#pragma once


class Window
{
public:

	Window (const char * windowName);
	~Window ();

	void resize (int x, int y);

	GPU_Target* getTarget ();
	GPU_Rect& getViewport ();

private:

	//Window vars
	int windowResX, windowResY;
	GPU_Target* screen;
	GPU_Rect viewport;
};

