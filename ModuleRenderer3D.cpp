#include "Globals.h"
#include "Application.h"
#include "ModuleRenderer3D.h"
#include "glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "ModuleFbx.h"
#include "ModuleInput.h"

#include <vector>
#include <cmath>


#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */


#define _USE_MATH_DEFINES



ModuleRenderer3D::ModuleRenderer3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

// Destructor
ModuleRenderer3D::~ModuleRenderer3D()
{}

// Called before render is available
bool ModuleRenderer3D::Init()
{
	LOG("Creating 3D Renderer context");
	bool ret = true;
	
	//OpenGL initialitzation
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	//Create context
	context = SDL_GL_CreateContext(App->window->window);
	if (context == NULL)
	{
		LOG("OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	//Init GLEW library
	GLenum err = glewInit();
	// … check for errors
	LOG("Using Glew %s", glewGetString(GLEW_VERSION));
	// Should be 2.0

	//detect current hardware and driver
	LOG("Vendor: %s", glGetString(GL_VENDOR));
	LOG("Renderer: %s", glGetString(GL_RENDERER));
	LOG("OpenGL version supported %s", glGetString(GL_VERSION));
	LOG("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	//reset projection and modelview matrices
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//OpenGL other options
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glClearDepth(1.0f);
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);

	App->m_fbx->Load("Assets/BakerHouse.fbx", v);


	if(ret == true)
	{
		//Use Vsync
		if(VSYNC && SDL_GL_SetSwapInterval(1) < 0)
			LOG("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());

		//Initialize Projection Matrix

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		//Check for error
		GLenum error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}

		//Initialize Modelview Matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//Check for error
		error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}
		
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glClearDepth(1.0f);
		
		//Initialize clear color
		glClearColor(0.f, 0.f, 0.f, 1.f);

		//Check for error
		error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}
		
		GLfloat LightModelAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LightModelAmbient);
		
		lights[0].ref = GL_LIGHT0;
		lights[0].ambient.Set(0.25f, 0.25f, 0.25f, 1.0f);
		lights[0].diffuse.Set(0.75f, 0.75f, 0.75f, 1.0f);
		lights[0].SetPos(0.0f, 0.0f, 2.5f);
		lights[0].Init();
		
		GLfloat MaterialAmbient[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MaterialAmbient);

		GLfloat MaterialDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MaterialDiffuse);
		
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		lights[0].Active(true);
		glEnable(GL_LIGHTING);
		glEnable(GL_COLOR_MATERIAL);
	}

	// Projection matrix for
	OnResize(SCREEN_WIDTH, SCREEN_HEIGHT);

	return ret;
}

// PreUpdate: clear buffer
update_status ModuleRenderer3D::PreUpdate(float dt)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(App->camera->GetViewMatrix());

	// light 0 on cam pos
	lights[0].SetPos(App->camera->Position.x, App->camera->Position.y, App->camera->Position.z);

	for(uint i = 0; i < MAX_LIGHTS; ++i)
		lights[i].Render();

	return UPDATE_CONTINUE;
}

update_status ModuleRenderer3D::Update(float dt)
{
	//drawCube();
	if (App->menu->wireframe)
	{
		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_LINE);
		for (int i = 0; i < v.size(); ++i)
		{
			v[i].DrawFbx();
		}
	}
	else {
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_FILL);
		for (int i = 0; i < v.size(); ++i)
		{
			v[i].DrawFbx();
		}
	}
	if (App->input->droped)
	{
		App->m_fbx->Load(App->input->dropped_filedir, v);
		App->input->droped = false;
	}

	return UPDATE_CONTINUE;

}


// PostUpdate present buffer to screen
update_status ModuleRenderer3D::PostUpdate(float dt)
{

	//ImGui::Render();
	//ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	//drawCubeDirectMode();
	//drawCubeVertexArray();
	//drawCubeIndex();
	//drawCircle();



	SDL_GL_SwapWindow(App->window->window);



	//App->level->Draw();
	//if (debug_draw == true)
	//{
	//	BeginDebugDraw();
	//	App->DebugDraw();
	//	EndDebugDraw();
	//}
	//App->editor->Draw();
	//SDL_GL_SwapWindow(App->window->GetWindow());


	//glClearColor(0.0, 0.0, 0.0, 0.0);
	//glClear(GL_COLOR_BUFFER_BIT);
	//glColor3f(1.0, 1.0, 1.0);
	//glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
	//glBegin(GL_POLYGON);
	//glVertex3f(0.25, 0.25, 0.0);
	//glVertex3f(0.75, 0.25, 0.0);
	//glVertex3f(0.75, 0.75, 0.0);
	//glVertex3f(0.25, 0.75, 0.0);
	//glEnd();
	//glFlush();



	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRenderer3D::CleanUp()
{
	LOG("Destroying 3D Renderer");

	SDL_GL_DeleteContext(context);

	return true;
}


void ModuleRenderer3D::OnResize(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	ProjectionMatrix = perspective(60.0f, (float)width / (float)height, 0.125f, 512.0f);
	glLoadMatrixf(&ProjectionMatrix);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//void ModuleRenderer3D::drawFBX(Vertex data)
//{
//	glEnableClientState(GL_VERTEX_ARRAY);
//
//	//-- Buffers--//
//	glBindBuffer(GL_ARRAY_BUFFER, data.id_vertex);
//	glVertexPointer(3, GL_FLOAT, 0, NULL);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data.id_index);
//
//	//-- Draw --//
//	glDrawElements(GL_TRIANGLES, data.num_index, GL_UNSIGNED_INT, NULL);
//
//	//-- UnBind Buffers--//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//	//--Disables States--//
//	glDisableClientState(GL_VERTEX_ARRAY);
//
//}


//void ModuleRenderer3D::drawCubeDirectMode()
//{
//	glBegin(GL_TRIANGLES);
//	// front faces
//	// face v0-v1-v2
//	glVertex3f(1, 1, 1);
//	glVertex3f(-1, 1, 1);
//	glVertex3f(-1, -1, 1);
//	// face v2-v3-v0
//	glVertex3f(-1, -1, 1);
//	glVertex3f(1, -1, 1);
//	glVertex3f(1, 1, 1);
//
//	// right faces
//	// face v0-v3-v4
//	glVertex3f(1, 1, 1);
//	glVertex3f(1, -1, 1);
//	glVertex3f(1, -1, -1);
//	// face v4-v5-v0
//	glVertex3f(1, -1, -1);
//	glVertex3f(1, 1, -1);
//	glVertex3f(1, 1, 1);
//
//	// top faces
//	// face v0-v5-v6
//	glVertex3f(1, 1, 1);
//	glVertex3f(1, 1, -1);
//	glVertex3f(-1, 1, -1);
//	// face v6-v1-v0
//	glVertex3f(-1, 1, -1);
//	glVertex3f(-1, 1, 1);
//	glVertex3f(1, 1, 1);
//
//	// left faces
//	// face  v1-v6-v7
//	glVertex3f(-1, 1, 1);
//	glVertex3f(-1, 1, -1);
//	glVertex3f(-1, -1, -1);
//	// face v7-v2-v1
//	glVertex3f(-1, -1, -1);
//	glVertex3f(-1, -1, 1);
//	glVertex3f(-1, 1, 1);
//
//	// bottom faces
//	// face v7-v4-v3
//	glVertex3f(-1, -1, -1);
//	glVertex3f(1, -1, -1);
//	glVertex3f(1, -1, 1);
//	// face v3-v2-v7
//	glVertex3f(1, -1, 1);
//	glVertex3f(-1, -1, 1);
//	glVertex3f(-1, -1, -1);
//
//	// back faces
//	// face v4-v7-v6
//	glVertex3f(1, -1, -1);
//	glVertex3f(-1, -1, -1);
//	glVertex3f(-1, 1, -1);
//	// face v6-v5-v4
//	glVertex3f(-1, 1, -1);
//	glVertex3f(1, 1, -1);
//	glVertex3f(1, -1, -1);
//
//	
//
//	glEnd();
//}


// array is 108 floats (36 * 3 = 108).
//GLfloat vertices[] = { 1, 1, 1,  -1, 1, 1,  -1,-1, 1,      // v0-v1-v2 (front)
//					   -1,-1, 1,   1,-1, 1,   1, 1, 1,      // v2-v3-v0
//
//						1, 1, 1,   1,-1, 1,   1,-1,-1,      // v0-v3-v4 (right)
//						1,-1,-1,   1, 1,-1,   1, 1, 1,      // v4-v5-v0
//
//						1, 1, 1,   1, 1,-1,  -1, 1,-1,      // v0-v5-v6 (top)
//					   -1, 1,-1,  -1, 1, 1,   1, 1, 1,      // v6-v1-v0
//
//					   -1, 1, 1,  -1, 1,-1,  -1,-1,-1,      // v1-v6-v7 (left)
//					   -1,-1,-1,  -1,-1, 1,  -1, 1, 1,      // v7-v2-v1
//
//					   -1,-1,-1,   1,-1,-1,   1,-1, 1,      // v7-v4-v3 (bottom)
//						1,-1, 1,  -1,-1, 1,  -1,-1,-1,      // v3-v2-v7
//
//						1,-1,-1,  -1,-1,-1,  -1, 1,-1,      // v4-v7-v6 (back)
//					   -1, 1,-1,   1, 1,-1,   1,-1,-1 };    // v6-v5-v4
//
//
//
//void ModuleRenderer3D::drawCubeVertexArray()
//{
//	
//	glGenBuffers(1, (GLuint*)&(my_id));
//	//glBindBuffer(GL_ARRAY_BUFFER, my_id);
//
//	//glDeleteBuffers(1, (GLuint*)&(my_id));
//
//	glEnableClientState(GL_VERTEX_ARRAY); //enable vertex array
//
//	glVertexPointer(3, GL_FLOAT, 0, vertices);
//
//	glTranslatef(8, 0, 0);
//	glDrawArrays(GL_TRIANGLES, 0, num_vertices);
//
//
//	glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
//
//}
//
//// vertices required to draw a cube.
//GLfloat vertices2[] = { 1, 1, 1,  -1, 1, 1,  -1,-1, 1,   1,-1, 1,   // v0,v1,v2,v3 (front)
//						1, 1, 1,   1,-1, 1,   1,-1,-1,   1, 1,-1,   // v0,v3,v4,v5 (right)
//						1, 1, 1,   1, 1,-1,  -1, 1,-1,  -1, 1, 1,   // v0,v5,v6,v1 (top)
//					   -1, 1, 1,  -1, 1,-1,  -1,-1,-1,  -1,-1, 1,   // v1,v6,v7,v2 (left)
//					   -1,-1,-1,   1,-1,-1,   1,-1, 1,  -1,-1, 1,   // v7,v4,v3,v2 (bottom)
//						1,-1,-1,  -1,-1,-1,  -1, 1,-1,   1, 1,-1 }; // v4,v7,v6,v5 (back)
//
//// index array of vertex array for glDrawElements() & glDrawRangeElement()
//GLubyte indices[] = { 0, 1, 2,   2, 3, 0,      // front
//					   4, 5, 6,   6, 7, 4,      // right
//					   8, 9,10,  10,11, 8,      // top
//					  12,13,14,  14,15,12,      // left
//					  16,17,18,  18,19,16,      // bottom
//					  20,21,22,  22,23,20 };    // back
//
//
//void ModuleRenderer3D::drawCubeIndex()
//{
//
//	//GLuint vboId1;
//	//GLuint vboId2;
//	//glGenBuffers(1, &vboId1);
//	//glGenBuffers(1, &vboId2);
//	// bind VBOs for vertex array and index array
//	//glBindBuffer(GL_ARRAY_BUFFER, vboId1);            // for vertex attributes
//	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboId2);    // for indices
//
//	// enable and specify pointers to vertex arrays
//
//	glEnableClientState(GL_VERTEX_ARRAY);
//
//	glVertexPointer(3, GL_FLOAT, 0, vertices2);
//
//	glTranslatef(-8, 0, 0);
//
//	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, indices);
//
//
//	glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
//
//
//	//glBindBuffer(GL_ARRAY_BUFFER, 0);
//	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//
//}
//
//
//
//void ModuleRenderer3D::drawCircle()
//{
//
//}
//
//void ModuleRenderer3D::drawTriangle()
//{
//
//}