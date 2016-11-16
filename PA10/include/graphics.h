#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

#include "graphics_headers.h"
#include "camera.h"
#include "shader.h"
#include "model.h"
#include "sphere.h"
#include "ground.h"
#include "cylinder.h"
#include "cube.h"
#include "walls.h"


struct Light
   {
    glm::vec4 AmbientProduct;
    glm::vec4 DiffuseProduct;
    glm::vec4 SpecularProduct;
    glm::vec4 LightPosition;
    float coneAngle;
    glm::vec3 coneDirection;
    float attenuation;
   };

class Graphics
{
  public:
    Graphics( btDiscreteDynamicsWorld* DynamicsWorld );
    ~Graphics();
    bool Initialize(int width, int height, std::string fNames[] );
    void Update(unsigned int dt, string motion[] );
    void Render();
    void setLightingUniforms( Model* object );
    void swapShaders( string shader );
    void adjustLighting( string control );
    
  private:
    std::string ErrorString(GLenum error);

    Camera *m_camera;
    Shader *m_shaderGouraud;
    Shader *m_shaderPhong;
    Shader *m_shader;

    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;

    btDiscreteDynamicsWorld* dynamicsWorld;

    Ground *m_ground;
    Sphere *m_sphere;
    Cylinder *m_cylinder;
    Cube *m_cube;
    Walls *m_walls;
    
    vector<Light> lights;
    
    unsigned long int counter = 0;
   
};

#endif /* GRAPHICS_H */
