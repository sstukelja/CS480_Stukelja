#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "graphics_headers.h"

class Object
{
  public:
    Object();
    ~Object();
    void Update(unsigned int dt, bool direction, int pause);
    void Render();

    glm::mat4 GetModel();
    glm::mat4 GetModel2();
    bool LoadObj();

  private:
    glm::mat4 model;
    glm::mat4 model2;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;

    float angle;
    float stopAngle;
};

#endif /* OBJECT_H */
