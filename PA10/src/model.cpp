#include "model.h"
#include <iostream>
#include <Magick++.h>

using namespace std;
using namespace Magick;

// Constructor
Model::Model( string file )
   {
    // Load meshes
    mesh.loadMesh( file );
    shininess = 0.7;
   }

Model::Model( string file, btTriangleMesh*& objTriMesh )
   {
    mesh.loadMesh( file, objTriMesh );
    shininess = 0.7;
   }
// Draws the model by drawing each mesh
void Model::Draw()
   {
    // Draw meshes
    mesh.Draw();
   }
    
// Updates the model based on physics
void Model::Update( btDiscreteDynamicsWorld* dynamicsWorld, unsigned int dt )
   {
    btTransform trans;
    btScalar m[ 16 ];
    
    rigidBody->getMotionState()->getWorldTransform( trans );
    
    trans.getOpenGLMatrix( m );
    
    model = glm::make_mat4( m );
   } 

// Returns mat4 of this Model
glm::mat4 Model::getModel()
    {
     return model;
    }
    
    
float Model::getShininess()
   {
    return shininess;
   }

void Model::adjustShininess( string control )
   {
    if( control == "UP" )
       {
        shininess += 0.1;
       }
    else
       {
        shininess -= 0.1;
       }
   }
