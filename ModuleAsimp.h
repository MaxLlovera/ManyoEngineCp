#pragma once
#include "Module.h"
#include "Globals.h"

#include "glew/include/glew.h"
#include "SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl3.h"


struct Vertex{
	uint id_index = 0; // index in VRAM
	uint num_index = 0;
	uint* index = nullptr;
	uint id_vertex = 0; // unique vertex in VRAM
	uint num_vertex = 0;
	float* vertex = nullptr;
};

class ModuleAsimp : public Module
{
public:
	ModuleAsimp(Application* app, bool start_enabled = true);

	~ModuleAsimp();

	void Load();

	update_status PreUpdate(float dt) override;
	bool Start() override;
	update_status Update(float dt) override;
	bool CleanUp() override;

private:
	Vertex v;

};
