#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"

#include <vector>
struct Vertex {
	uint id_index = 0; // index in VRAM
	uint num_index = 0;
	uint* index = nullptr;

	uint id_vertex = 0; // unique vertex in VRAM
	uint num_vertex = 0;
	float* vertex = nullptr;

	//Tex
	uint id_tex = 0;
	//uint textureID = 0;
	uint num_tex = 0;
	float* texCoords = nullptr;
	GLuint textureID;
	
	//float* tex = nullptr;
	


	void CreateBuffer();
	void CreateBufferTex(const void* checkerImage);
	void DrawFbx();

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
	void Load(const char* path, std:: vector<Vertex> &v);
	//void LoadTex(const char* path, const aiScene* scene);
	
	//void CreateBuffer(Vertex &data);
	//void DrawFbx(Vertex &data);

	//int num_meshes = 0;

public:
	
};
