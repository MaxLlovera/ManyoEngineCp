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

//struct Vertex {
//	uint id_index = 0; // index in VRAM
//	uint num_index = 0;
//	uint* index = nullptr;
//	uint id_vertex = 0; // unique vertex in VRAM
//	uint num_vertex = 0;
//	float* vertex = nullptr;
//
//	CreateBuffer();
//	DrawFbx();
//
//};

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();


	bool Start();
	update_status Update(float dt);
	bool CleanUp();

private:
	//Vertex v;

};

