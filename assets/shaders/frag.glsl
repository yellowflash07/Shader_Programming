
varying vec3 fColor;
varying vec2 fTex;

uniform sampler2D tex;
uniform sampler2D tex2;

void main() 
{
	gl_FragColor = vec4(fColor.rgb,1.0);
}