#pragma once
#include "Globals.h"
#include "glew/include/glew.h"
#include "SDL/include/SDL_opengl.h"
#include <gl/GLU.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl3.h"
#include <gl/GL.h>
#include "GameObject.h"

enum Type {
	TRANSFORM_COMPONENT,
	MESH_COMPONENT,
	MATERIAL_COMPONENT
};
class Component
{
public:
	Component() {}
	~Component();

	bool Active();
	GameObject* GameObject();

	virtual void Enable();
	virtual void Update();
	virtual void Disable();

private:
	Type type;
};
