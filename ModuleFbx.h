#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"

struct Vertex {
	uint id_index = 0; // index in VRAM
	uint num_index = 0;
	uint* index = nullptr;
	uint id_vertex = 0; // unique vertex in VRAM
	uint num_vertex = 0;
	float* vertex = nullptr;
};

class ModuleFbx : public Module
{
public:
	ModuleFbx(Application* app, bool start_enabled = true);
	~ModuleFbx();

	bool Init() override;
	update_status PreUpdate(float dt) override;
	update_status Update(float dt) override;
	update_status PostUpdate(float dt) override;
	bool CleanUp() override;
	void Load();

private:
	Vertex v;

};
