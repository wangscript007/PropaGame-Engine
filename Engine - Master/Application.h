#pragma once

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleRenderExercise;
class ModuleEditor;
class ModuleCamera;
class ModuleShader;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();
	void Tick();

public:
	ModuleRender* renderer = nullptr;
	ModuleWindow* window = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleInput* input = nullptr;
    ModuleRenderExercise* exercise = nullptr;
	ModuleEditor* editor = nullptr;
	ModuleCamera* camera = nullptr;
	ModuleShader* shader = nullptr;

	float lastTickCount = 0;	// How many ticks passed last time it was checked
	float deltaTime = 0;		// Time in seconds
	int FPS = 0;				// How many frames have passed in one second
	int frameCounter = 0;		// Counter to count frames
	float auxTimer = 0;			// Timer to check when a second has passed

private:

	std::list<Module*> modules;

};

extern Application* App;
