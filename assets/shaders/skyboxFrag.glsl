#version 420 core

in vec3 TexCoords;
out vec4 FragColor;

uniform samplerCube cubeMap;

void main()
{
    FragColor = texture(cubeMap, normalize(TexCoords));
}