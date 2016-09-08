#include <iostream>
#include <fstream>
#include <string>

#include "engine.h"

using namespace std;

extern string vertexPath;
extern string fragmentPath;

int main(int argc, char **argv)
{
  // Check to see if the correct amount of arguments were passed
  if(argc != 3)
  {
    cout << "Incorrect number of arugments" << endl;
    cout << "Use format: ./Executable <vertexFilename> <fragmentFilename>" << endl;
    return 1;
  }
  // Pathing that offsets to shaders directory
  string v = "../shaders/";
  string f = "../shaders/";

  // Adjusts pathing to correct file
  string vertexPath = v.append(argv[1]);
  string fragmentPath = f.append(argv[2]);

  // Instantiation of fstream variables
  fstream vertexFile;
  fstream fragmentFile;

  // Attempt to open both files
  vertexFile.open(vertexPath);
  fragmentFile.open(fragmentPath);

  if(!(vertexFile.is_open()))
  {
    cout << "Could not open vertex shader file" << endl;
    return 1;
  }
  if(!(fragmentFile.is_open()))
  {
    cout << "Could not open fragment shader file" << endl;
    return 1;
  }

  vertexFile.close();
  fragmentFile.close();

  // Start an engine and run it then cleanup after
  Engine *engine = new Engine("Tutorial Window Name", 800, 600);
  if(!engine->Initialize())
  {
    printf("The engine failed to start.\n");
    delete engine;
    engine = NULL;
    return 1;
  }
  engine->Run();
  delete engine;
  engine = NULL;
  return 0;
}
