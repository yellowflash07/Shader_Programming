
varying vec3 fColor;
varying vec2 fTex;
varying vec2 fNormal;

uniform sampler2D tex;
uniform sampler2D tex2;

vec3 ambient;

void main() 
{
    vec3 finalColor = vec3(0.0f);
	ambient = vec3(0.3f);
	finalColor = ambient;
	gl_FragColor = vec4(finalColor.rgb,1.0);
}