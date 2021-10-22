#include "Globals.h"
#include "Application.h"
#include "ModuleAsimp.h"
#include "Primitive.h"
#include <Windows.h>

#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#pragma comment (lib, "assimp/libx86/assimp-vc142-mtd.lib")

ModuleAsimp::ModuleAsimp(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleAsimp::~ModuleAsimp()
{}

// Load assets
bool ModuleAsimp::Start()
{

    bool ret = true;


    return ret;
}

update_status ModuleAsimp::PreUpdate(float dt)
{
    // Stream log messages to Debug window
    struct aiLogStream stream;
    stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
    aiAttachLogStream(&stream);

    //Load();

    return UPDATE_CONTINUE;
}


// Update: draw background
update_status ModuleAsimp::Update(float dt)
{


    return UPDATE_CONTINUE;
}

// Load assets
bool ModuleAsimp::CleanUp()
{
    LOG("Unloading Intro scene");
    // detach log stream
    aiDetachAllLogStreams();
    return true;
}


void ModuleAsimp::Load()
{

    const aiScene* scene = aiImportFile("Assets/warrior.fbx", aiProcessPreset_TargetRealtime_MaxQuality);
    if (scene != nullptr && scene -> HasMeshes())
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