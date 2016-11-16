#ifndef MESH_H
#define MESH_H

#include <vector>
#include "graphics_headers.h"
#include "shader.h"
#include "texture.h"

#define INVALID_MATERIAL 0xffffffff
#define INVALID_OGL_VALUE 0xffffffff

using namespace std;

// Data structure for individual meshes
struct MeshEntry
   {
    // Constructor
    MeshEntry();
    
    // Destructor
    ~MeshEntry();

    // Initialize data members and buffers for an individual mesh
    void Init( vector<Vertex>& Vertices, vector<unsigned int>& Indices );

    // Buffer objects
    GLuint VBO;
    GLuint IBO;
    
    unsigned int numIndices;
    
    // Identifies which texture applies to this specific mesh
    unsigned int materialIndex;
   };

// Datat structure that holds all meshes and textures for a model
class Mesh
   {
    public:
       // Constructor
       Mesh();

       // Destructor
       ~Mesh();

       // Load mesh using ASSIMP and ImageMagick
       bool loadMesh( string& fileName );
       bool loadMesh( string& fileName, btTriangleMesh*& objTriMesh  );


       // Output textured mesh
       void Draw();

    private:
       // Functions used to help load mesh
       bool loadScene(const aiScene* scene );
       void initMesh(unsigned int Index, const aiMesh* mesh );
       void initTriMesh(unsigned int Index, const aiMesh* mesh );
       bool loadMaterials(const aiScene* scene );
       
       // Deallocates textures 
       void Clear();

       // Vector of the meshes for this model
       vector<MeshEntry> meshEntries;
       btTriangleMesh* m_objTriMesh;
       
       // Vector of all the model's specified textures
       vector<Texture*> meshTextures;
   };


#endif 
