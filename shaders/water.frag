

//varying vec3 Normal;
uniform vec3 ObjColor;
uniform samplerCube skybox;
varying vec3 norm;
varying vec3 viewVec;

void main () 
{
	  // Reflective ray (when hitting the object)
	vec3 ref = reflect(viewVec, norm);

	


	float fog = (gl_Fog.end - gl_FogFragCoord) * gl_Fog.scale;
	vec4 colorFog = texture(skybox, ref);
	gl_FragColor = 	mix(gl_Fog.color, colorFog, fog);
	
	
	// Cube map lookup

	 gl_FragColor = vec4(0,0,0.9,0.5);
	}