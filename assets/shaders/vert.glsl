
layout (location= 0)attribute vec3 vPos;
layout (location= 1)attribute vec3 vCol;
layout (location= 2)attribute vec2 vTex;


varying vec3 fColor;
varying vec2 fTex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main() 
{
    mat4 mvp = projection * view * model;
	gl_Position = mvp * vec4(vPos.xyz, 1.0);

	fColor = vCol;
	fTex = vTex;
}