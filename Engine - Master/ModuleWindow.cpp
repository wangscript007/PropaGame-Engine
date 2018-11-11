#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"

ModuleWindow::ModuleWindow()
{
}

// Destructor
ModuleWindow::~ModuleWindow()
{
}

// Called before render is available
bool ModuleWindow::Init()
{
	LOG("Init SDL window & surface");
	bool ret = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		//Create window
		SDL_GetCurrentDisplayMode(0, &DM);
		DM.w -= 100;
		DM.h -= 78;
		screen_width = DM.w;
		screen_height = DM.h;

		Uint32 flags = SDL_WINDOW_SHOWN |  SDL_WINDOW_OPENGL;
		
		//Set window settings
		if(fullscreen) flags |= SDL_WINDOW_FULLSCREEN;
		if(resizable) flags |= SDL_WINDOW_RESIZABLE;
		SDL_GL_SetSwapInterval(vsync);

		window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, flags);

		if(window == NULL)
		{
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			//Get window surface
			
			screen_surface = SDL_GetWindowSurface(window);
		}
	}

	return ret;
}

update_status ModuleWindow::Update() {

	if (screen_width != DM.w || screen_height != DM.h)
		SetWindowSize(screen_width, screen_height, true);

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleWindow::CleanUp()
{
	LOG("Destroying SDL window and quitting all SDL systems");

	//Destroy window
	if(window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}

const void ModuleWindow::ToggleFullScreen() 
{
	Uint32 fullscreenFlag = SDL_WINDOW_FULLSCREEN;
	bool isFullscreen = SDL_GetWindowFlags(window) & fullscreenFlag;
	SDL_SetWindowFullscreen(window, isFullscreen ? 0 : fullscreenFlag);
	SDL_ShowCursor(isFullscreen);

	SDL_GetCurrentDisplayMode(0, &DM);
	// If it was on fullscreen change make window a bit smaller than screen
	if (isFullscreen)
	{
		DM.w -= 100;
		DM.h -= 78;
	}
	SetWindowSize(DM.w, DM.h, true);
}

const void ModuleWindow::ToggleVSync()
{
	SDL_GL_SetSwapInterval(!SDL_GL_GetSwapInterval());
}

const void ModuleWindow::ToggleResizable()
{
	Uint32 resizableFlag = SDL_WINDOW_RESIZABLE;
	bool isResizable = SDL_GetWindowFlags(window) & resizableFlag;
	SDL_SetWindowResizable(window, (SDL_bool)!isResizable);
}

const void ModuleWindow::ToggleBorderless()
{
	Uint32 resizableFlag = SDL_WINDOW_BORDERLESS;
	bool isResizable = SDL_GetWindowFlags(window) & resizableFlag;
	SDL_SetWindowBordered(window, (SDL_bool)!borderless);
}

const void ModuleWindow::SetWindowBrightness(int value)
{
	SDL_SetWindowBrightness(window, brightness);
}

const void ModuleWindow::SetWindowSize(int w, int h, bool useSDL)
{
	DM.w = w;
	DM.h = h;
	screen_width = w;
	screen_height = h;
	glViewport(0, 0, screen_width, screen_height);
	//App->camera->UpdateScreenSize();
	if(useSDL)
		SDL_SetWindowSize(window, screen_width, screen_height);
}

