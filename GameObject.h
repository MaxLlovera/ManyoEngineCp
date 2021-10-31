#pragma once
#include "Globals.h"
#include "glew/include/glew.h"
#include "SDL/include/SDL_opengl.h"
#include <gl/GLU.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl3.h"
#include <gl/GL.h>

#include <vector>
#include <string>
class Component;

class GameObject
{
public:
	GameObject() {}
	~GameObject();

	void Update();
	//Component* CreateComponent(Type type);

	
public:
	std::string name;
	std::vector<Component*> compoments;
	GameObject* parent;
	std::vector<GameObject*> children;

};
