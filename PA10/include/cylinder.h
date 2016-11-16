#ifndef CYLINDER_H
#define CYLINDER_H

#include <vector>
#include "graphics_headers.h"
#include "model.h"
#include <string>

using namespace std;

// Derived from Model Class
class Cylinder: public Model
{
    public:
        // Constructor
        Cylinder( string fileName, btDiscreteDynamicsWorld* dynamicsWorld );
        
        void Update( btDiscreteDynamicsWorld* dynamicsWorld, unsigned int dt );
        
        // Destructor
        ~Cylinder();

    private:
    
};

#endif
