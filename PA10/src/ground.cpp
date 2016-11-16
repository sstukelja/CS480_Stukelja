#include "ground.h"
#include <vector>
#include <cmath>

using namespace std;

Ground::Ground( string fileName, btDiscreteDynamicsWorld* dynamicsWorld ) : Model( fileName, m_objTriMesh  )
   {
    // Create ground collision shape
    btCollisionShape* groundShape = 
                                new btBvhTriangleMeshShape( m_objTriMesh, true);
    
    // Create ground motion state, place 1 meter below ground
    btDefaultMotionState* groundMotionState = new btDefaultMotionState( 
    btTransform( btQuaternion( 0, 0, 0, 1 ), btVector3( 0, -1, 0 ) ) );
            
    // Create groud rigid body, set mass 0 (immovable)
    btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI( 
                      0, groundMotionState, groundShape, btVector3( 0, 0, 0 ) );
    rigidBody = new btRigidBody( groundRigidBodyCI );
            
    // Add ground to world
    dynamicsWorld->addRigidBody( rigidBody );
   }
