#include "walls.h"
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

Walls::Walls( btDiscreteDynamicsWorld* dynamicsWorld )
   {
    // Create collision shapes
    btCollisionShape* ceilingShape = new btStaticPlaneShape( btVector3( 0, 1, 0 ), btScalar(0) );
        
    // Create motion states
    btDefaultMotionState* ceilingMotionState = new btDefaultMotionState( 
    btTransform( btQuaternion( 0, 0, 0, 1 ), btVector3( 0, 1, 0 ) ) );            

    // Create rigid bodies
    btScalar mass = 0;
    btVector3 Inertia = btVector3( 0, 0, 0 );
    
    ceilingShape->calculateLocalInertia( mass, Inertia );
    
    btRigidBody::btRigidBodyConstructionInfo ceilingRigidBodyCI( 
                                mass, ceilingMotionState, ceilingShape, Inertia );


    ceilingBody = new btRigidBody( ceilingRigidBodyCI );

    ceilingBody->setRestitution( 0.1 );
                        
    // Add bodies to world
    dynamicsWorld->addRigidBody( ceilingBody );   
   }

void Walls::Update( btDiscreteDynamicsWorld* dynamicsWorld )
   {

   } 

