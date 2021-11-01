#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include "Module.h"
#include "SDL/include/SDL.h"

class Application;

class ModuleWindow : public Module
{
public:

	ModuleWindow(Application* app, bool start_enabled = true);

	// Destructor
	virtual ~ModuleWindow();

	bool Init() override;
	bool CleanUp() override;

	void SetTitle(const char* title);
	const char* GetTitle();
	void SetFullScreen(bool fullScreen);
	void SetResizable(bool resizable);
	void SetBrightness(float brightness);
	void SetWindowSize(int width, int height);
	void SetFullDesktop(bool &fullDesktop);
	void SetBorderless(bool borderless);
	void SetVsync(bool vsync);

	void GetWindowSize(int &width, int &height);
	//int GetRefreshRate();
	
	float GetBrightness();


public:
	//The window we'll be rendering to
	SDL_Window* window;

	//The surface contained by the window
	SDL_Surface* screen_surface;
};

#endif // __ModuleWindow_H__