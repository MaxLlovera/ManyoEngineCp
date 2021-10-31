#pragma once
#include "Globals.h"
#include "Application.h"
#include "ModuleRenderer3D.h"
#include "glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "ModuleFbx.h"

#include <vector>
#include <cmath>


#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */


#define _USE_MATH_DEFINES


void drawPyramid()
{
	glBegin(GL_TRIANGLES);

	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	glVertex3f(0.0f, 1.f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(0.0f, -1.0f, -1.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(0.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	glEnd();
}


