#include "object.h"
#include <iostream>
#include "SDL.h"
#include <cmath>
#include <fstream>
using namespace std;

Object::Object()
{  
  /*
    # Blender File for a Cube
    o Cube
    v 1.000000 -1.000000 -1.000000
    v 1.000000 -1.000000 1.000000
    v -1.000000 -1.000000 1.000000
    v -1.000000 -1.000000 -1.000000
    v 1.000000 1.000000 -0.999999
    v 0.999999 1.000000 1.000001
    v -1.000000 1.000000 1.000000
    v -1.000000 1.000000 -1.000000
    s off
    f 2 3 4
    f 8 7 6
    f 1 5 6
    f 2 6 7
    f 7 8 4
    f 1 4 8
    f 1 2 4
    f 5 8 6
    f 2 1 6
    f 3 2 7
    f 3 7 4
    f 5 1 8
  */

  Vertices = {
    {{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 0.0f}},
    {{1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
    {{-1.0f, -1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
    {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}},
    {{1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 0.0f}},
    {{1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0f}},
    {{-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 1.0f}},
    {{-1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}}
  };

  Indices = {
    2, 3, 4,
    8, 7, 6,
    1, 5, 6,
    2, 6, 7,
    7, 8, 4,
    1, 4, 8,
    1, 2, 4,
    5, 8, 6,
    2, 1, 6,
    3, 2, 7,
    3, 7, 4,
    5, 1, 8
  };

  // The index works at a 0th index
  for(unsigned int i = 0; i < Indices.size(); i++)
  {
    Indices[i] = Indices[i] - 1;
  }

  angle = 0.0f;

  glGenBuffers(1, &VB);
  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &IB);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);
}

Object::~Object()
{
  Vertices.clear();
  Indices.clear();
}

void Object::Update(unsigned int dt, bool direction, int pause)
{
    // CCW
    if(direction)
    {
        switch(pause)
        {
            // 0 is normal state, 1 is stopping rotation, 2 is stopping orbit, and 3 is complete pause
            case 0:
            stopAngle -= (dt * M_PI/1000);
            angle -= (dt * M_PI/1000);
  	        model = glm::translate(glm::mat4(1.0f), glm::vec3(5.0 * cos(angle), 0.0, 5.0 * sin(angle))) * glm::rotate(glm::mat4(1.0f), (angle), 
            glm::vec3(0.0, 5.0, 0.0));
            model2 = glm::translate(glm::mat4(model), glm::vec3(5.0 * sin(angle), 0.0, 5.0 * cos(angle))) * glm::rotate(glm::mat4(1.0f), (angle), 
            glm::vec3(0.0, 5.0, 0.0));
            break;
            case 1:
            stopAngle -= (dt * M_PI/1000);
            angle -= (dt * M_PI/1000);
  	        model = glm::translate(glm::mat4(1.0f), glm::vec3(5.0 * cos(angle), 0.0, 5.0 * sin(angle))) * glm::rotate(glm::mat4(1.0f), (angle * 0), 
            glm::vec3(0.0, 5.0, 0.0));
            model2 = glm::translate(glm::mat4(model), glm::vec3(5.0 * sin(angle), 0.0, 5.0 * cos(angle))) * 
            glm::rotate(glm::mat4(1.0f), (angle), glm::vec3(0.0, 5.0, 0.0));
            break;
            case 2:
            angle -= (dt * M_PI/1000);
  	        model = glm::translate(glm::mat4(1.0f), glm::vec3(5.0 * cos(stopAngle), 0.0, 5.0 * sin(stopAngle))) * glm::rotate(glm::mat4(1.0f), (angle), glm::vec3(0.0, 5.0, 0.0));
            model2 = glm::translate(glm::mat4(model), glm::vec3(5.0 * sin(angle), 0.0, 5.0 * cos(angle))) * 
            glm::rotate(glm::mat4(1.0f), (angle), glm::vec3(0.0, 5.0, 0.0));
            break;
            case 3:
            stopAngle -= (dt * M_PI/1000);
            angle -= (0 * M_PI/1000);
  	        model = glm::translate(glm::mat4(1.0f), glm::vec3(5.0 * cos(angle), 0.0, 5.0 * sin(angle))) * glm::rotate(glm::mat4(1.0f), (angle), 
            glm::vec3(0.0, 5.0, 0.0));
            model2 = glm::translate(glm::mat4(model), glm::vec3(5.0 * sin(angle), 0.0, 5.0 * cos(angle))) * 
            glm::rotate(glm::mat4(1.0f), (angle), glm::vec3(0.0, 5.0, 0.0));
        }
    }
    // CW
    if(!direction)
    {
        switch(pause)
        {
            // 0 is normal state, 1 is stopping rotation, 2 is stopping orbit, and 3 is complete pause
            case 0:
            stopAngle += (dt * M_PI/1000);
            angle += (dt * M_PI/1000);
      	    model = glm::translate(glm::mat4(1.0f), glm::vec3(5.0 * cos(angle), 0.0, 5.0 * sin(angle))) * 
            glm::rotate(glm::mat4(1.0f), (angle), glm::vec3(0.0, 5.0, 0.0));
            model2 = glm::translate(glm::mat4(model), glm::vec3(5.0 * sin(angle), 0.0, 5.0 * cos(angle))) * 
            glm::rotate(glm::mat4(1.0f), (angle), glm::vec3(0.0, 5.0, 0.0));
            break;
            case 1:
            stopAngle += (dt * M_PI/1000);
            angle += (dt * M_PI/1000);
  	        model = glm::translate(glm::mat4(1.0f), glm::vec3(5.0 * cos(angle), 0.0, 5.0 * sin(angle))) * glm::rotate(glm::mat4(1.0f), (angle * 0), 
            glm::vec3(0.0, 5.0, 0.0));
             model2 = glm::translate(glm::mat4(model), glm::vec3(5.0 * sin(angle), 0.0, 5.0 * cos(angle))) * 
            glm::rotate(glm::mat4(1.0f), (angle), glm::vec3(0.0, 5.0, 0.0));
            break;
            case 2:
            angle += (dt * M_PI/1000);
  	        model = glm::translate(glm::mat4(1.0f), glm::vec3(5.0 * cos(stopAngle), 0.0, 5.0 * sin(stopAngle))) * glm::rotate(glm::mat4(1.0f), (angle), 
            glm::vec3(0.0, 5.0, 0.0));
             model2 = glm::translate(glm::mat4(model), glm::vec3(5.0 * sin(angle), 0.0, 5.0 * cos(angle))) * 
            glm::rotate(glm::mat4(1.0f), (angle), glm::vec3(0.0, 5.0, 0.0));
            break;
            case 3:
            stopAngle += (dt * M_PI/1000);
            angle += (0 * M_PI/1000);
  	        model = glm::translate(glm::mat4(1.0f), glm::vec3(5.0 * cos(angle), 0.0, 5.0 * sin(angle))) * glm::rotate(glm::mat4(1.0f), (angle), 
            glm::vec3(0.0, 5.0, 0.0));
             model2 = glm::translate(glm::mat4(model), glm::vec3(5.0 * sin(angle), 0.0, 5.0 * cos(angle))) * 
            glm::rotate(glm::mat4(1.0f), (angle), glm::vec3(0.0, 5.0, 0.0));
            break;
        }
    }
}

glm::mat4 Object::GetModel()
{
  return model;
}

glm::mat4 Object::GetModel2()
{
  return model2;
}

void Object::Render()
{
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,color));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

  glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}

bool Object::LoadObj()
{
    string line;
    ifstream fin;
    fin.open("../models/box.obj");
    if(!(fin.is_open()))
    {
        return false;
    }

    while(fin.good())
    {
        fin >> line;
        if(line[0] == 'v' && line[1] != 'n')
        {
            glm::vec3 vertex;
            fin >> vertex.x;
            fin >> vertex.y;
            fin >> vertex.z;
            fin.ignore(100, '\n');
            cout << "Vertex: " << vertex.x << " " << vertex.y << " " << vertex.z << endl;
        }
        else
        {
            fin.ignore(300, '\n');
        }
    }
    fin.close();
    return true;

}

