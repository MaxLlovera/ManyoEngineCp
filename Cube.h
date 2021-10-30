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


GLfloat vertices1[] = { 1, 1, 1,  -1, 1, 1,  -1,-1, 1,      // v0-v1-v2 (front)
					   -1,-1, 1,   1,-1, 1,   1, 1, 1,      // v2-v3-v0

						1, 1, 1,   1,-1, 1,   1,-1,-1,      // v0-v3-v4 (right)
						1,-1,-1,   1, 1,-1,   1, 1, 1,      // v4-v5-v0

						1, 1, 1,   1, 1,-1,  -1, 1,-1,      // v0-v5-v6 (top)
					   -1, 1,-1,  -1, 1, 1,   1, 1, 1,      // v6-v1-v0

					   -1, 1, 1,  -1, 1,-1,  -1,-1,-1,      // v1-v6-v7 (left)
					   -1,-1,-1,  -1,-1, 1,  -1, 1, 1,      // v7-v2-v1

					   -1,-1,-1,   1,-1,-1,   1,-1, 1,      // v7-v4-v3 (bottom)
						1,-1, 1,  -1,-1, 1,  -1,-1,-1,      // v3-v2-v7

						1,-1,-1,  -1,-1,-1,  -1, 1,-1,      // v4-v7-v6 (back)
					   -1, 1,-1,   1, 1,-1,   1,-1,-1 };    // v6-v5-v4

// normal array
GLfloat normals1[] = { 0, 0, 1,   0, 0, 1,   0, 0, 1,      // v0-v1-v2 (front)
						0, 0, 1,   0, 0, 1,   0, 0, 1,      // v2-v3-v0

						1, 0, 0,   1, 0, 0,   1, 0, 0,      // v0-v3-v4 (right)
						1, 0, 0,   1, 0, 0,   1, 0, 0,      // v4-v5-v0

						0, 1, 0,   0, 1, 0,   0, 1, 0,      // v0-v5-v6 (top)
						0, 1, 0,   0, 1, 0,   0, 1, 0,      // v6-v1-v0

					   -1, 0, 0,  -1, 0, 0,  -1, 0, 0,      // v1-v6-v7 (left)
					   -1, 0, 0,  -1, 0, 0,  -1, 0, 0,      // v7-v2-v1

						0,-1, 0,   0,-1, 0,   0,-1, 0,      // v7-v4-v3 (bottom)
						0,-1, 0,   0,-1, 0,   0,-1, 0,      // v3-v2-v7

						0, 0,-1,   0, 0,-1,   0, 0,-1,      // v4-v7-v6 (back)
						0, 0,-1,   0, 0,-1,   0, 0,-1 };    // v6-v5-v4

void drawCube()
{
	// enble and specify pointers to vertex arrays
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normals1);
	glVertexPointer(3, GL_FLOAT, 0, vertices1);

	glPushMatrix();
	glTranslatef(2, 2, 0);                  // move to upper-right corner

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glPopMatrix();

	glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
	glDisableClientState(GL_NORMAL_ARRAY);
}

