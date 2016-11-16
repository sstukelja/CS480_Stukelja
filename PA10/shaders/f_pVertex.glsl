#version 330
          
          in vec4 color; 
          in vec2 texture;
          
          out vec4 frag_color;

          uniform sampler2D gSampler;
          
          void main(void) 
          {  
             frag_color = color * texture2D( gSampler, texture.xy ); 
          } 
          
          
          
