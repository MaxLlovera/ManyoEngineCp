#include "Application.h"
#include <list>


Application::Application()
{
	window = new ModuleWindow(this);
	input = new ModuleInput(this);
	audio = new ModuleAudio(this, true);
	scene_intro = new ModuleSceneIntro(this);
	renderer3D = new ModuleRenderer3D(this);
	camera = new ModuleCamera3D(this);
	menu = new ModuleMenu(this);

	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	AddModule(camera);
	AddModule(input);
	AddModule(audio);
	AddModule(menu);
	
	// Scenes
	AddModule(scene_intro);

	// Renderer last!
	AddModule(renderer3D);
}

Application::~Application()
{
	for(std::list<Module*>::iterator it = list_modules.begin(); it != list_modules.end(); ++it)
	{
		delete (*it);
	}

}

bool Application::Init()
{
	bool ret = true;

	// Call Init() in all modules

	for (std::list<Module*>::iterator it = list_modules.begin(); it != list_modules.end(); ++it)
	{
		ret = (*it)->Init();
		
	}

	// After all Init calls we call Start() in all modules
	LOG("Application Start --------------");

	for (std::list<Module*>::iterator it = list_modules.begin(); it != list_modules.end(); ++it)
	{
		ret = (*it)->Start();

	}
	
	ms_timer.Start();
	return ret;
}

// ---------------------------------------------
void Application::PrepareUpdate()
{
	dt = (float)ms_timer.Read() / 1000.0f;
	ms_timer.Start();
}

// ---------------------------------------------
void Application::FinishUpdate()
{
}

// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	PrepareUpdate();
	
	for (std::list<Module*>::iterator it = list_modules.begin(); it != list_modules.end() && (ret == UPDATE_CONTINUE); ++it)
	{
		ret = (*it)->PreUpdate(dt);
	}

	//item = list_modules.getFirst();

	for (std::list<Module*>::iterator it = list_modules.begin(); it != list_modules.end() && (ret == UPDATE_CONTINUE); ++it)
	{
		ret = (*it)->Update(dt);
	}

	//item = list_modules.getFirst();

	for (std::list<Module*>::iterator it = list_modules.begin(); it != list_modules.end() && (ret == UPDATE_CONTINUE); ++it)
	{
		ret = (*it)->PostUpdate(dt);
	}

	FinishUpdate();
	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for (std::list<Module*>::iterator it = list_modules.begin(); it != list_modules.end(); ++it)
	{
		ret = (*it)->CleanUp();
	}
	return ret;
}

void Application::AddModule(Module* mod)
{
	list_modules.push_back(mod);
}