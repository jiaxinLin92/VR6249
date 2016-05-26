varying vec3 norm;
varying vec3 viewVec;


uniform samplerCube spaceship;

void main(void)
{
	// Reflective ray (when hitting the object)
	vec3 ref = reflect(viewVec, norm);
	
	// Cube map lookup
	gl_FragColor = texture(spaceship, ref);
}