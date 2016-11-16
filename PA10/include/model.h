#ifndef MODEL_H
#define MODEL_H

#include "graphics_headers.h"
#include "mesh.h"
#include <string>

using namespace std;

class Model 
   {
    public:
        Model( string file );
        Model( string file, btTriangleMesh *& objTriMesh );
        void Draw();	
		void Update( btDiscreteDynamicsWorld* dynamicsWorld, unsigned int dt );
		glm::mat4 getModel();
		float getShininess();
		void adjustShininess( string control );

    protected:
        Mesh mesh;
		glm::mat4 model;
		float rotateAngle;
		float shininess;
        btRigidBody* rigidBody;
   };
   
#endif
