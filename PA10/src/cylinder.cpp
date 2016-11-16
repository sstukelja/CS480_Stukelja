#include "cylinder.h"
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

Cylinder::Cylinder( string fileName, btDiscreteDynamicsWorld* dynamicsWorld ) : Model( fileName )
   {
    // Create cylinder collision shape
    btCollisionShape* cylinderShape = new btBoxShape( btVector3( 1, 1, 1 ) );
        
    // Create cylinder motion state, place 50 meters above ground
    btDefaultMotionState* cylinderMotionState = new btDefaultMotionState( 
    btTransform( btQuaternion( 0, 0, 0, 1 ), btVector3( 0, 1, -10 ) ) );            
            
    // Create Cylinder rigid body
    btScalar mass = 0;
    btVector3 cylinderInertia = btVector3( 0, 0, 0 );
    cylinderShape->calculateLocalInertia( mass, cylinderInertia );
    btRigidBody::btRigidBodyConstructionInfo cylinderRigidBodyCI( 
                                mass, cylinderMotionState, cylinderShape, cylinderInertia );
    rigidBody = new btRigidBody( cylinderRigidBodyCI );
    
    rigidBody->setRestitution( .001 );
                        
    // Add cylinder to world
    dynamicsWorld->addRigidBody( rigidBody );    
   }

void Cylinder::Update( btDiscreteDynamicsWorld* dynamicsWorld, unsigned int dt )
   {
    btTransform trans;
    btScalar m[ 16 ];
    
    rigidBody->getMotionState()->getWorldTransform( trans );
    
    trans.getOpenGLMatrix( m );
    
    model = glm::make_mat4( m );
   } 
