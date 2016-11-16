#include "sphere.h"
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

Sphere::Sphere( string fileName, btDiscreteDynamicsWorld* dynamicsWorld ) : Model( fileName )
   {
    // Create sphere collision shape
    btCollisionShape* fallShape = new btSphereShape( 1 );
        
    // Create sphere motion state, place 50 meters above ground
    btDefaultMotionState* fallMotionState = new btDefaultMotionState( 
    btTransform( btQuaternion( 0, 0, 0, 1 ), btVector3( -23, 3, -30 ) ) );            
            
    // Create Sphere rigid body
    btScalar mass = 10;
    btVector3 fallInertia = btVector3( 0, 0, 0 );
    fallShape->calculateLocalInertia( mass, fallInertia );
    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI( 
                                mass, fallMotionState, fallShape, fallInertia );
    rigidBody = new btRigidBody( fallRigidBodyCI );

    rigidBody->setLinearFactor(btVector3( 1, 1, 1 ) );
    rigidBody->setAngularFactor(btVector3( 0, 0, 0 ) );

    rigidBody->setRestitution(0.9);
                        
    // Add sphere to world
    dynamicsWorld->addRigidBody( rigidBody );    
   }

void Sphere::Update( btDiscreteDynamicsWorld* dynamicsWorld, unsigned int dt )
   {
    btTransform trans;
    btScalar m[ 16 ];
    
    rigidBody->getMotionState()->getWorldTransform( trans );
    
    trans.getOpenGLMatrix( m );
    
    model = glm::make_mat4( m );
   } 

void Sphere::Start()
{
    rigidBody->applyCentralImpulse( btVector3(0,0,1000));
}
