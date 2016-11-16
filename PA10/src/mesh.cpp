#include "mesh.h"

// MeshEntry Constructor
MeshEntry::MeshEntry()
   {
    // Initialize buffers and data members
    VBO = INVALID_OGL_VALUE;
    IBO = INVALID_OGL_VALUE;
    numIndices  = 0;
    materialIndex = INVALID_MATERIAL;
   };

// MeshEntry Destructor
MeshEntry::~MeshEntry()
   {
    // Delete buffers if they have data
    if (VBO != INVALID_OGL_VALUE)
       {
        glDeleteBuffers(1, &VBO);
       }
    if (IBO != INVALID_OGL_VALUE)
       {
        glDeleteBuffers(1, &IBO);
       }
   }

// Create buffers from vertex and index data
void MeshEntry::Init( vector<Vertex>& Vertices, vector<unsigned int>& Indices)
   {
    // Initialize function/variables
    numIndices = Indices.size();

    // Vertex buffer
    glGenBuffers(1, &VBO);
  	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

    // Index buffer
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numIndices, &Indices[0], GL_STATIC_DRAW);
   }
   
// Constructor
Mesh::Mesh()
   {
    m_objTriMesh = NULL;
   }

// Destructor
Mesh::~Mesh()
   {
    Clear();
   }
   
// Texture deallocation
void Mesh::Clear()
   {
    // Initialize function/variables
    int index;
    
    // Loop through all textures    
    for ( index = 0 ; index < meshTextures.size() ; index++) 
       {
        // Check if texture was allocated
        if( meshTextures[ index ] != NULL );
           {
            // Delete texture
            delete meshTextures[ index ];
           }
       }
    // end loop
    
   }

// Load model using ASSIMP 
bool Mesh::loadMesh( string& fileName )
   {   
    // Initialize function/variables
    fileName = "models/" + fileName;
    Assimp::Importer Importer;
    Clear();
    
    // Get ASSIMP scene object
    const aiScene* scene = Importer.ReadFile(fileName.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_OptimizeMeshes );
    
    // Check if failure loading scene from file
    if ( !scene ) 
       {
        cout << "ASSIMP error loading: " << fileName << ": " <<endl
             << " " << Importer.GetErrorString(); 
        return false;
       }
       
    return loadScene( scene );
   }

bool Mesh::loadMesh( string& fileName, btTriangleMesh*& objTriMesh  )
   {   
    // Initialize function/variables
    fileName = "models/" + fileName;
    Assimp::Importer Importer;
    Clear();
    
    objTriMesh = new btTriangleMesh();
    m_objTriMesh = objTriMesh;
    
    // Get ASSIMP scene object
    const aiScene* scene = Importer.ReadFile(fileName.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices );
    
    // Check if failure loading scene from file
    if ( !scene ) 
       {
        cout << "ASSIMP error loading: " << fileName << ": " <<endl
             << " " << Importer.GetErrorString(); 
        return false;
       }
       
    return loadScene( scene );
   }

bool Mesh::loadScene(const aiScene* scene )
   {  
    // Initialize function/variables
    int index;
    meshEntries.resize( scene->mNumMeshes );
    meshTextures.resize( scene->mNumMaterials );
    
    // Loop through all meshes in the model
    for( index = 0 ; index < meshEntries.size() ; index++) 
       {
        // Initialize the current mesh
        const aiMesh* mesh = scene->mMeshes[ index ];
        
        if( m_objTriMesh == NULL )
           {
            initMesh( index, mesh );
           }
        else
           {
            initTriMesh( index, mesh );
           }

       }

    // Get textures
    return loadMaterials( scene );
   } 

// Loads vertex, index, and texture coordinates for a single mesh
void Mesh::initMesh( unsigned int Index, const aiMesh* mesh )
   {
    // Initialize function/variables
    int index;
    meshEntries[Index].materialIndex = mesh->mMaterialIndex;

    vector<Vertex> Vertices;
    vector<unsigned int> Indices;

    glm::vec2 vec;
    glm::vec4 vector; 
    glm::vec3 normal; 
    Vertex vertex;
    
    // Loop through all vertices
    for( index = 0 ; index < mesh->mNumVertices ;index++ ) 
       {
        // Vertex coordinates
        vector.x = mesh->mVertices[ index ].x;
        vector.y = mesh->mVertices[ index ].y;
        vector.z = mesh->mVertices[ index ].z;
        vector.w = 1.0f;
        
        vertex.vertex = vector;
        
        // Vertex normals
        normal.x = mesh->mNormals[ index ].x;
        normal.y = mesh->mNormals[ index ].y;
        normal.z = mesh->mNormals[ index ].z;
            
            
        // Check if texture coordinates specified    
        if(mesh->mTextureCoords[0])
           {
            // Load Texture coordinates
            vec.x = mesh->mTextureCoords[0][ index ].x; 
            vec.y = mesh->mTextureCoords[0][ index ].y;

            vertex.texCoords = vec;
           }
        // Otherwise, assume no texture coordinates
        else
           {
            vertex.texCoords = glm::vec2(0.0f, 0.0f);
           }   
 
        // Store current vertex
        Vertices.push_back( vertex );
       }
    // end loop
    
    // Loop through all faces
    for(GLuint meshIndex = 0; meshIndex < mesh->mNumFaces; meshIndex++)
       {       
        // Get the indices associated with the current face
        aiFace face = mesh->mFaces[ meshIndex ];

        for(GLuint index = 0; index < face.mNumIndices; index++)
           {
            Indices.push_back( face.mIndices[ index ] );
           }
       }
    // end loop
    
    // Initialize current mesh's buffers
    meshEntries[ Index ].Init( Vertices, Indices );
   }

// Loads vertex, index, and texture coordinates for a single mesh
void Mesh::initTriMesh( unsigned int Index, const aiMesh* mesh )
   {
    // Initialize function/variables
    int index;
    meshEntries[Index].materialIndex = mesh->mMaterialIndex;

    vector<Vertex> Vertices;
    vector<unsigned int> Indices;

    glm::vec2 vec;
    glm::vec4 vector; 
    glm::vec3 normal; 
    Vertex vertex;
    
    // Loop through all vertices
    for( index = 0 ; index < mesh->mNumVertices ;index++ ) 
       {
        // Vertex coordinates
        vector.x = mesh->mVertices[ index ].x;
        vector.y = mesh->mVertices[ index ].y;
        vector.z = mesh->mVertices[ index ].z;
        vector.w = 1.0f;
        
        vertex.vertex = vector;
        
        // Vertex normals
        normal.x = mesh->mNormals[ index ].x;
        normal.y = mesh->mNormals[ index ].y;
        normal.z = mesh->mNormals[ index ].z;
            
            
        // Check if texture coordinates specified    
        if(mesh->mTextureCoords[0])
           {
            // Load Texture coordinates
            vec.x = mesh->mTextureCoords[0][ index ].x; 
            vec.y = mesh->mTextureCoords[0][ index ].y;

            vertex.texCoords = vec;
           }
        // Otherwise, assume no texture coordinates
        else
           {
            vertex.texCoords = glm::vec2(0.0f, 0.0f);
           }   
 
        // Store current vertex
        Vertices.push_back( vertex );
       }
    // end loop
    
    // Loop through all faces
    for(GLuint meshIndex = 0; meshIndex < mesh->mNumFaces; meshIndex++)
       {       
        btVector3 triArray[ 3 ];
        
        // Get the indices associated with the current face
        aiFace face = mesh->mFaces[ meshIndex ];

        for(GLuint index = 0; index < face.mNumIndices; index++)
           {
            aiVector3D position = mesh->mVertices[ face.mIndices[ index ] ];
            triArray[ index ] = btVector3( position.x, position.y, position.z );
            
            Indices.push_back( face.mIndices[ index ] );
           }

        m_objTriMesh->addTriangle( triArray[ 0 ], triArray[ 1 ], triArray[ 2 ] );
       }
    // end loop
    
    // Initialize current mesh's buffers
    meshEntries[ Index ].Init( Vertices, Indices );
   }

// Loads texture for current mesh using ImageMagick (in Texture function)
bool Mesh::loadMaterials(const aiScene* scene )
   {
    // Initialize function/variables
    bool result = true;
    int index;
    
    // Loop through model's materials
    for( index = 0; index < scene->mNumMaterials; index++) 
       {
        const aiMaterial* pMaterial = scene->mMaterials[ index ];

        meshTextures[ index ] = NULL;

        if (pMaterial->GetTextureCount( aiTextureType_DIFFUSE ) > 0) 
           {
            aiString Path;

            if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) 
               {
                string file = string( Path.C_Str() );
                
                meshTextures[ index ] = new Texture( GL_TEXTURE_2D, file );

                // Attempt to laod texture 
                if( !meshTextures[ index ]->Load() ) 
                   {
                    // Output error message
                    cout << "Could not load texture: " << Path.C_Str() << endl;
                    delete meshTextures[ index ];
                    meshTextures[ index ] = NULL;
                    result = false;
                   }
               }
           }
       }

    return result;
   }

void Mesh::Draw()
   {
    // Initialize function/variables
    int index;
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    int MaterialIndex;
    
    // Loop through each mesh in the model
    for( index = 0 ; index < meshEntries.size() ; index++ ) 
       {
        // Bind vertex and index buffers
        glBindBuffer(GL_ARRAY_BUFFER, meshEntries[ index ].VBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)20);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshEntries[ index ].IBO);

        // Get material index for current mesh ( if it has one )
        int MaterialIndex = meshEntries[ index ].materialIndex;

        // Check if mesh has a texture
        if( MaterialIndex < meshTextures.size() && meshTextures[ MaterialIndex ] ) 
           {
            // Bind the current mesh's texture
            meshTextures[ MaterialIndex ]->Bind( GL_TEXTURE0 );
           }
           
        // Draw the mesh
        glDrawElements(GL_TRIANGLES, meshEntries[ index ].numIndices, GL_UNSIGNED_INT, 0);
       }
    // end loop
    
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

   }

