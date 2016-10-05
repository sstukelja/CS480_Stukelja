#ifndef MESH_H
#define MESH_H

#include <vector>
#include "graphics_headers.h"

using namespace std;

class Mesh
{
    public:
        // Constructor
        Mesh(vector<Vertex> vertices, vector<GLuint> indices/*, vector<Texture> textures*/);

        void Draw(/* Shader shader*/);
        
    private:
        // Data
        vector<Vertex> vertices;
        vector<GLuint> indices;
        //vector<Texture> textures;
        GLuint VAO, VBO, EBO;
};

#endif /* MESH_H */
