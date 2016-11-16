#ifndef GROUND_H
#define GROUND_H

#include <vector>
#include "graphics_headers.h"
#include "model.h"
#include <string>

using namespace std;

// Derived from Model Class
class Ground: public Model
{
    public:
        // Constructor
        Ground( string fileName, btDiscreteDynamicsWorld* dynamicsWorld );

        // Destructor
        ~Ground();

    private:
        btTriangleMesh* m_objTriMesh; 
};

#endif
