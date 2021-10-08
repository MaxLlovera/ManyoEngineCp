#pragma once
#include "Module.h"
#include "Globals.h"
#include "glew/include/glew.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl2.h"
#include <gl/GL.h>

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();


	bool Start();
	update_status Update(float dt);
	bool CleanUp();

public:
};

