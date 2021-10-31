#pragma once
#include <vector>

#include "Module.h"
#include "Globals.h"

#include "glew/include/glew.h"
#include "SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Primitive.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl3.h"


using namespace std;

class ModuleMenu : public Module
{
public:
	ModuleMenu(Application* app, bool start_enabled = true);
	~ModuleMenu();

	bool show_demo_window = false;
	bool show_another_window = false;
	bool show_debug_window = false;

	bool show_app_main_menu_bar = false;
	bool show_app_about = false;
	bool about_us = false;
	bool active = false;
	bool resizable = true;
	bool fullscreen = false;
	bool fullDesktop = false;
	bool borderless = true;

	bool createCube = false;
	bool createSphere = false;
	bool createPyramid = false;

	bool showConsole = false;
	bool showOptions = false;
	bool showLibrary = false;
	//enable/disable
	bool depthTest = true;
	bool cullFace = true;
	bool lighting = true;
	bool colorMaterial = true;
	bool texture2D = true;
	bool wireframe = false;

	//bool wireframeOn = false;

	//two more

	char name[32];
	char organization[32];
	vector<float> fps_log;
	vector<float> ms_log;

	int max_fps = 0;

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	ImVec4 color_hardware = ImVec4(1.0f, 1.0f, 0.0f, 1.00f);

	bool Start() override;
	update_status Update(float dt) override;
	bool CleanUp() override;
	void SetWireFrameMode(bool wireframe);
	void SetDepthTest(bool depthTest);
	void SetCullFace(bool cullFace);
	void SetLighting(bool lighting);
	void SetColorMaterial(bool colorMaterial);
	void SetTexture2D(bool texture2D);

	//Console c;
	Cube* cube;

public:
};