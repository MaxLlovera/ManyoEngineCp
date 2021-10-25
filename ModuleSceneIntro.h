#pragma once
#include "Module.h"
#include "Globals.h"
#include "glew/include/glew.h"
#include "SDL/include/SDL_opengl.h"
#include <gl/GLU.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl3.h"
#include <gl/GL.h>
#include "ModuleFbx.h"

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();


	bool Start();
	update_status Update(float dt);
	bool CleanUp();

private:
	Vertex v;
	Vertex data;
};

