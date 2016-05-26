
varying vec2 texCoord;
uniform sampler2D color;
uniform sampler2D light;

void main(void)
{   
	gl_FragColor = texture2D(color, texCoord.xy)*0.5 + texture2D(light, texCoord.xy)*0.5;
}