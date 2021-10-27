#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"
#include <vector>
#define MAX_LIGHTS 8


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

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(Application* app, bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init() override;
	update_status PreUpdate(float dt) override;
	update_status Update(float dt) override;
	update_status PostUpdate(float dt) override;
	bool CleanUp() override;

	//void drawFBX(Vertex data);

	void OnResize(int width, int height);

	void drawCubeDirectMode();
	void drawCubeVertexArray();
	void drawCubeIndex();
	void drawCircle();
	void drawTriangle();

public:

	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;


	int num_vertices = 36;
	uint my_id = 0;

	std::vector<Vertex> v;
};