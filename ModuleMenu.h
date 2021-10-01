#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl2.h"
#include <gl/GL.h>

class ModuleMenu : public Module
{
public:
	ModuleMenu(Application* app, bool start_enabled = true);
	~ModuleMenu();

	bool show_demo_window = false;
	bool show_another_window = false;
	bool show_debug_window = false;

	bool show_app_main_menu_bar = false;
	bool about_us = false;


	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

public:
};