#ifndef GRAPHICS_HEADERS_H
#define GRAPHICS_HEADERS_H

#include <iostream>

#define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED

#if defined(__APPLE__) || defined(MACOSX)
  #include <OpenGL/gl3.h>
  #include <OpenGL/GLU.h>
#else //linux as default
  #include <GL/glew.h>
  //#include <GL/glu.h>
#endif

// GLM for matricies
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

// Headers for Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// Headers for ImageMagick
#include <Magick++.h>

// Headers for Bullet
#include <btBulletDynamicsCommon.h>
#include <bullet/BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h>
#include <bullet/BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h>

// Headers for file IO
#include <fstream>
#include <sstream>

using namespace std;

#define INVALID_UNIFORM_LOCATION 0x7fffffff

struct Vertex
{
  glm::vec4 vertex;
  glm::vec2 texCoords;
  glm::vec3 normals;

  Vertex() {}
  Vertex(glm::vec4 v, glm::vec3 n, glm::vec2 t): vertex(v), normals(n), texCoords(t) {}
};

#endif /* GRAPHICS_HEADERS_H */
