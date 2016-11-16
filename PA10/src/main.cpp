#include <cstdlib>
#include <string>
#include <algorithm>
#include "engine.h"

using namespace std;

/*
Function returns whether or not input is formatted correctly. Only returns true 
if both vertex and fragment shaders are specified in the correct format.

Stores vertex shader filename in inputData[ 1 ]
Stores fragment shader filename in inputData[ 2 ]
*/
bool validateInput( int numArgs, char **inputStrings, string inputData[] );

bool checkEndsWith( const string& testString, const string& endStr );

int main(int argc, char **argv)
{
    // Initialize program/variables
    string inputInfo[ 3 ];
  
    // Check if shaders and object were specified correctly
    if( validateInput( argc, argv, inputInfo ) )
    {
        // Start an engine and run it then cleanup after
        Engine *engine = new Engine("Tutorial Window Name", 1600, 900);
        if(!engine->Initialize( inputInfo ))
        {
          printf("The engine failed to start.\n");
          delete engine;
          engine = NULL;
   
        }
      
        engine->Run();
        delete engine;
        engine = NULL;
    }
    
    return 0;  
}

bool validateInput( int numArgs, char **inputStrings, string inputData[] )
{
 bool result = false;
 
 if( numArgs > 1 )
    {
     inputData[ 0 ] = inputStrings[ 1 ];
     result = true;
    }
 else
    {
     cout << "ERROR: Please specify 'Gouraud' or 'Phong' for lighting" << endl;
    }
    
 return result;
}

bool checkEndsWith( const string& testString, const string& endStr )
{
    // Initialize function/variables
    int sizeDiff = testString.length() - endStr.length();
    
    // Check if ending string can be contained in test string
    if( testString.size() >= endStr.length() )
    {
        // Compare end of test string to ending string
        return ( testString.compare( sizeDiff, endStr.length(), endStr ) == 0 );
    }
    else
    {
        return false;
    }
}




