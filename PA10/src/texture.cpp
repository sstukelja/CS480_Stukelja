#include <iostream>
#include "texture.h"


Texture::Texture()
   {

   }
   
Texture::Texture( GLenum textureTarget, const string& fileName )
   {
    m_textureTarget = textureTarget;
    m_fileName = "models/" + fileName;
   }


bool Texture::Load()
   {
    try 
       {
        m_image.read(m_fileName);
        m_image.write(&m_blob, "RGBA");
       }
    catch (Magick::Error& Error) 
       {
        cout << "Error loading texture '" << m_fileName << "': " << Error.what() << std::endl;
        return false;
       }

    glGenTextures(1, &m_textureObj);
    glBindTexture(GL_TEXTURE_2D, m_textureObj);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_image.columns(), m_image.rows(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_blob.data());
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    return true;
   }

void Texture::Bind(GLenum TextureUnit)
   {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture( GL_TEXTURE_2D, m_textureObj );
   }
