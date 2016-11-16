 #version 330
          const int MAX_LIGHTS = 10;

          struct Light
             {
              vec4 AmbientProduct;
              vec4 DiffuseProduct;
              vec4 SpecularProduct;
              vec4 LightPosition;
              float coneAngle;
              vec3 coneDirection;
              float attenuation;
             };
          
          layout (location = 0) in vec3 v_position; 
          layout (location = 1) in vec2 v_texture; 
          layout (location = 2) in vec3 v_normal; 
          
          out vec4 color; 
          out vec2 texture;
          
          uniform int numLights;          
          uniform Light lights[ MAX_LIGHTS ];
          uniform mat4 projectionMatrix; 
          uniform mat4 viewMatrix;
          uniform mat4 modelMatrix; 
          uniform float Shininess;
          
          void main(void) 
          { 
            vec4 v = vec4( v_position, 1.0 );
            float attenuation = 1.0;
            vec3 surfaceToLight;
            mat4 ModelView = viewMatrix * modelMatrix;
            vec3 pos = ( ModelView * v ).xyz;
            
            vec4 ambient = vec4( 0.0 );
            vec4 diffuse = vec4( 0.0 );
            vec4 specular = vec4( 0.0 );
            
            for( int index = 0; index < numLights; index++ )
               {
                vec3 L = normalize( lights[ index ].LightPosition.xyz - pos );
                vec3 E = normalize( -pos );
                vec3 H = normalize( L + E );

                // Check for directional light
                if( lights[ index ].LightPosition.w == 0.0 )
                   {
                    surfaceToLight = normalize( lights[ index ].LightPosition.xyz);
                    attenuation = 1.0;
                   }               
                 // Otherwise, assume point/spotlight
                 else
                    {
                     // Point light distance affecting attenuation
                     surfaceToLight = normalize( lights[ index ].LightPosition.xyz - pos );
                     float distanceToLight = length( L - pos );
                     attenuation = 1.0 / ( 1.0 + lights[ index ].attenuation * pow( distanceToLight, 2 ) );
                     
                     // Spotlight cone affecting attenuation
                     float lightToSurfaceAngle = degrees( acos ( dot (-surfaceToLight, normalize( lights[ index ].coneDirection ) ) ) );
                     if( lightToSurfaceAngle > lights[ index ].coneAngle )
                        {
                         attenuation = 0.0;
                        }
                    }
                
                vec3 N = normalize( ModelView * vec4( v_normal, 0.0 ) ).xyz;
                
                ambient += lights[ index ].AmbientProduct;
                
                float Kd = max( dot( L, N ), 0.0 );
                diffuse += Kd * lights[ index ].DiffuseProduct;
                
                float Ks = pow( max( dot( N, H ), 0.0 ), Shininess );
                specular += Ks * lights[ index ].SpecularProduct;
                
                if(dot( L, N ) < 0.0 )
                   {
                    specular += vec4( 0.0, 0.0, 0.0, 1.0 );
                   }
                   
                gl_Position = projectionMatrix * ModelView * v;     
               }

            
            color = ambient + attenuation * ( diffuse + specular );
            color.a = 1.0;
            
            texture = v_texture;
          } 
          
          
          
