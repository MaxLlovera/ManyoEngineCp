#include "Globals.h"
#include "Application.h"
#include "ModuleFbx.h"
#include "glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include <vector>
#include <cmath>

#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#pragma comment (lib, "assimp/libx86/assimp-vc142-mtd.lib")

ModuleFbx::ModuleFbx(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

// Destructor
ModuleFbx::~ModuleFbx()
{}

// Called before render is available
bool ModuleFbx::Init()
{
	LOG("Creating 3D Renderer context");
	bool ret = true;



	return ret;
}

// PreUpdate: clear buffer
update_status ModuleFbx::PreUpdate(float dt)
{

	// Stream log messages to Debug window
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);

	//Load();

	return UPDATE_CONTINUE;
	return UPDATE_CONTINUE;
}

update_status ModuleFbx::Update(float dt)
{


	return UPDATE_CONTINUE;

}


// PostUpdate present buffer to screen
update_status ModuleFbx::PostUpdate(float dt)
{



	return UPDATE_CONTINUE;
}

void ModuleFbx::Load()
{

    const aiScene* scene = aiImportFile("Assets/warrior.fbx", aiProcessPreset_TargetRealtime_MaxQuality);
    if (scene != nullptr && scene->HasMeshes())
    {
        // Use scene->mNumMeshes to iterate on scene->mMeshes array
        for (int i = 0; i < scene->mNumMeshes; ++i)
        {
            aiMesh* sceneM = scene->mMeshes[i];

            // copy vertices
            v.num_vertex = sceneM->mNumVertices;
            v.vertex = new float[v.num_vertex * 3];
            memcpy(v.vertex, sceneM->mVertices, sizeof(float) * v.num_vertex * 3);
            LOG("New mesh with %d vertices", v.num_vertex);

            // copy faces
            if (sceneM->HasFaces())
            {
                v.num_index = sceneM->mNumFaces * 3;
                v.index = new uint[v.num_index]; // assume each face is a triangle
                for (uint i = 0; i < sceneM->mNumFaces; ++i)
                {
                    if (sceneM->mFaces[i].mNumIndices != 3)
                    {
                        LOG("WARNING, geometry face with != 3 indices!");
                    }
                    else
                    {
                        memcpy(&v.index[i * 3], sceneM->mFaces[i].mIndices, 3 * sizeof(uint));
                    }

                }
            }
        }
        aiReleaseImport(scene);
    }
    else
        LOG("Error loading scene %s", "Assets/warrior.fbx");

}

// Called before quitting
bool ModuleFbx::CleanUp()
{
	LOG("Destroying 3D Renderer");

	aiDetachAllLogStreams();

	return true;
}


