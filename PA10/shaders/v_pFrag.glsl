 #version 330

          layout (location = 0) in vec3 v_position; 
          layout (location = 1) in vec2 v_texture; 
          layout (location = 2) in vec3 v_normal; 

          out vec3 fN;
          out vec3 fE;
          out vec3 surfacePos;
          out vec2 texture; 
          
          uniform mat4 projectionMatrix; 
          uniform mat4 viewMatrix;
          uniform mat4 modelMatrix; 
 
          void main(void) 
          { 
            surfacePos = vec3( modelMatrix * vec4( v_position, 1.0 ) );
            vec4 v = vec4( v_position, 1.0 );
            mat4 ModelView = viewMatrix * modelMatrix;
            fN = v_normal;
            fE = v_position;

            texture = v_texture;
             
            gl_Position = projectionMatrix * ModelView * v;     
          } 
          
          
          
