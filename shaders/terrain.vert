varying vec2 texCoord;
uniform sampler2D height;

void main()
{
	texCoord = gl_MultiTexCoord0.xy;
    gl_FrontColor = gl_Color;
	vec4 pos = gl_Vertex;
	pos.y = (texture2D(height, texCoord)*850.0).x-850.0;
	pos.x *= 6.0;
    gl_Position = gl_ModelViewProjectionMatrix * pos;
}


