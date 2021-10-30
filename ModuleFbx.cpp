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
#include "assimp/mesh.h"

#define CHECKERS_HEIGHT 256/4
#define CHECKERS_WIDTH  256/4


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

//void ModuleFbx::LoadTex(const char* path, const aiScene* scene)
//{
	// Check if scene has textures.
	//if (scene->HasTextures())
	//{
	//	textureIds = new GLuint[scene->mNumTextures];
	//	glGenTextures(scene->mNumTextures, textureIds);// generate GL-textures ID's
	//	// upload textures
	//	for (size_t ti = 0; ti < scene->mNumTextures; ti++)
	//	{
	//		glBindTexture(GL_TEXTURE_2D, textureIds[ti]);// Binding of texture name
	//		//
	//		//redefine standard texture values
	//		//
	//		// We will use linear interpolation for magnification filter
	//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//		// tiling mode
	//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (scene->mTextures[ti]->achFormatHint[0] & 0x01) ? GL_REPEAT : GL_CLAMP);
	//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (scene->mTextures[ti]->achFormatHint[0] & 0x01) ? GL_REPEAT : GL_CLAMP);
	//		// Texture specification
	//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, scene->mTextures[ti]->mWidth, scene->mTextures[ti]->mHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE,
	//			scene->mTextures[ti]->pcData);
	//	}
	//}
//}

void ModuleFbx::Load(const char* path, std::vector<Vertex>& v)
{

	GLubyte checkerImage[CHECKERS_HEIGHT][CHECKERS_WIDTH][4];
	for (int i = 0; i < CHECKERS_HEIGHT; i++) {
		for (int j = 0; j < CHECKERS_WIDTH; j++) {
			int c = ((((i & 0x8) == 0) ^ (((j & 0x8)) == 0))) * 255;
			checkerImage[i][j][0] = (GLubyte)c;
			checkerImage[i][j][1] = (GLubyte)c;
			checkerImage[i][j][2] = (GLubyte)c;
			checkerImage[i][j][3] = (GLubyte)255;
		}
	}



    const aiScene* scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);
    if (scene != nullptr && scene->HasMeshes())
    {
        // Use scene->mNumMeshes to iterate on scene->mMeshes array
		v.resize(scene->mNumMeshes);
        for (int i = 0; i < scene->mNumMeshes; ++i)
        {
			Vertex& _v = v[i];
            aiMesh* sceneM = scene->mMeshes[i];
			
			//aiVector3D* texM;

			// copy vertices
            _v.num_vertex = sceneM->mNumVertices;
            _v.vertex = new float[_v.num_vertex * 3];
            memcpy(_v.vertex, sceneM->mVertices, sizeof(float) * _v.num_vertex * 3);
            LOG("New mesh with %d vertices", _v.num_vertex);

            // copy faces
            if (sceneM->HasFaces())
            {
                _v.num_index = sceneM->mNumFaces * 3;
                _v.index = new uint[_v.num_index]; // assume each face is a triangle
                for (uint j = 0; j < sceneM->mNumFaces; ++j)
                {
                    if (sceneM->mFaces[j].mNumIndices != 3)
                    {
                        LOG("WARNING, geometry face with != 3 indices!");


                    }
                    else 
                    {
                        memcpy(&_v.index[j * 3], sceneM->mFaces[j].mIndices, 3 * sizeof(uint));
					//	//copy textures
					//	if (sceneM->HasTextureCoords(0))
					//	{
					//		glTexCoord2f(sceneM->mTextureCoords[0][i * 3 + j].x, 1 - sceneM->mTextureCoords[0][i * 3 + j].y);
					//	}
                    }
					//glVertex3fv(&sceneM->mVertices[_v.num_index].x);


                }
            }

			// copy tex coords
			_v.texCoords = new float[_v.num_vertex * 2];
			for (size_t k = 0; k < sceneM->mNumVertices; k++) {
				if (sceneM->mTextureCoords[0]) {
					_v.texCoords[k * 2] = sceneM->mTextureCoords[0][k].x;
					_v.texCoords[k * 2 + 1] = sceneM->mTextureCoords[0][k].y;
				}
			}
			
				//_v.textureIds = new GLuint[scene->mNumTextures];
				//glGenTextures(scene->mNumTextures, _v.textureIds);// generate GL-textures ID's
				// upload textures
				//for (size_t ti = 0; ti < scene->mNumTextures; ti++)
				//{
				//	glBindTexture(GL_TEXTURE_2D, _v.textureIds[ti]);// Binding of texture name
				//	//
				//	//redefine standard texture values
				//	//
				//	// We will use linear interpolation for magnification filter
				//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				//	// tiling mode
				//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (scene->mTextures[ti]->achFormatHint[0] & 0x01) ? GL_REPEAT : GL_CLAMP);
				//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (scene->mTextures[ti]->achFormatHint[0] & 0x01) ? GL_REPEAT : GL_CLAMP);
				//	// Texture specification
				//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, scene->mTextures[ti]->mWidth, scene->mTextures[ti]->mHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE,
				//		scene->mTextures[ti]->pcData);
				//}
			
			/*LoadTex(path, scene);*/
			/*if (sceneM->HasTextureCoords(i))
			{
				_v.texCoords = new float[_v.num_index * 3];
				memcpy(_v.texCoords, sceneM->mTextureCoords, sizeof(float) * _v.num_index * 3);
				//_v.texCoords = sceneM->mTextureCoords;
			}*/

            //Vertex _v = v;
            _v.CreateBuffer();
			_v.CreateBufferTex(checkerImage);
        }
        aiReleaseImport(scene);
    }
    else
        LOG("Error loading scene %s", "Assets/warrior.fbx");

}





void Vertex::CreateBuffer()
{
    glGenBuffers(1,&id_vertex);
    glBindBuffer(GL_ARRAY_BUFFER, id_vertex);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * num_vertex * 3, vertex, GL_STATIC_DRAW);

    glGenBuffers(1, &id_index);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_index);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * num_index, index, GL_STATIC_DRAW);
}

void Vertex::CreateBufferTex(const void *checkerImage)
{
	
	glGenBuffers(1, &textureID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, textureID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * num_tex, texCoords, GL_STATIC_DRAW);
	//abans
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * num_tex, tex, GL_STATIC_DRAW);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	//ara
	/*glGenTextures(1, &id_tex);
	glBindTexture(GL_TEXTURE_2D, id_tex);*/
	//abans
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, CHECKERS_WIDTH, CHECKERS_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkerImage);

	//glEnable(GL_TEXTURE_2D);
}


void Vertex::DrawFbx()
{

    glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);
    //-- Buffers--//
    glBindBuffer(GL_ARRAY_BUFFER, id_vertex);
    glVertexPointer(3, GL_FLOAT, 0, NULL);

	//glBindBuffer(GL_ARRAY_BUFFER, id_tex);
	//abans
	glBindBuffer(GL_ARRAY_BUFFER, textureID);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);
	
	//glBindTexture(GL_TEXTURE_2D, id_tex);
	//abans
	glBindTexture(GL_TEXTURE_2D, textureID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_index);

    //-- Draw --//
    glDrawElements(GL_TRIANGLES, num_index, GL_UNSIGNED_INT, NULL);

    //-- UnBind Buffers--//
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_TEXTURE_COORD_ARRAY, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

    //--Disables States--//
    glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

// Called before quitting
bool ModuleFbx::CleanUp()
{
	LOG("Destroying 3D Renderer");

	aiDetachAllLogStreams();

	return true;
}


