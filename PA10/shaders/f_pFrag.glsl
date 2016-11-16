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
          
          in vec3 fN;
          in vec3 fE;
          in vec3 surfacePos;
          in vec2 texture; 
          
          out vec4 frag_color; 
          
          uniform int numLights;
          uniform Light lights[ MAX_LIGHTS ];
          uniform sampler2D gSampler;
          uniform float Shininess;
          
          void main(void) 
          { 
            vec4 ambient = vec4( 0.0 );
            vec4 diffuse = vec4( 0.0 );
            vec4 specular = vec4( 0.0 );
            vec3 surfaceToLight;
            float attenuation = 1.0;
            
            for( int index = 0; index < numLights; index++ )
               {  
                vec3 fL = lights[ index ].LightPosition.xyz;
             
                if( lights[ index ].LightPosition.w != 0.0 ) 
                   {
    	            fL -= fE;
    	           }

                vec3 N = normalize( fN );
                vec3 E = normalize( fE );
                vec3 L = normalize( fL );
                vec3 H = normalize( L + E );
                
                // Check for directional light
                if( lights[ index ].LightPosition.w == 0.0 )
                   {
                    surfaceToLight = normalize( lights[ index ].LightPosition.xyz );
                    attenuation = 1.0;
                   }               
                 // Otherwise, assume point/spotlight
                 else
                    {
                     // Point light attenuation
                     surfaceToLight = normalize( lights[ index ].LightPosition.xyz - surfacePos );
                     attenuation = lights[ index ].attenuation;
                     
                     // Spotlight cone affecting attenuation
                     float lightToSurfaceAngle = degrees( acos ( dot (-surfaceToLight, normalize( lights[ index ].coneDirection ) ) ) );
                     if( lightToSurfaceAngle > lights[ index ].coneAngle )
                        {
                         attenuation = 0.0;
                        }
                    }
                
                ambient += lights[ index ].AmbientProduct;
                
                float Kd = max( dot( L, N ), 0.0 );
                diffuse += Kd * lights[ index ].DiffuseProduct;
                
                float Ks = pow( max( dot( N, H ), 0.0 ), Shininess );
                specular += Ks * lights[ index ].SpecularProduct;
                
                if(dot( L, N ) < 0.0 )
                specular += vec4( 0.0, 0.0, 0.0, 1.0 );
               }
             
             frag_color = ambient + attenuation * ( diffuse + specular );
             frag_color *= texture2D( gSampler, texture.xy );
             frag_color.a = 1.0; 
          } 
          
          
          
