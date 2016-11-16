#ifndef TEXTURE_H
#define TEXTURE_H

#include "graphics_headers.h"
#include <string>

using namespace std;

class Texture
   {
    public:
      Texture();
      Texture( GLenum textureTarget, const string& fileName );

      bool Load();

      void Bind( GLenum TextureUnit );
      
    private:
       string m_fileName;
       GLenum m_textureTarget;
       GLuint m_textureObj;
       Magick::Image m_image;
       Magick::Blob m_blob;
   };



#endif 
