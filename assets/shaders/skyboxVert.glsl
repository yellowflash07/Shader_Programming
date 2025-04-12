#version 420 core

layout (location = 0) in vec3 vPos;

out vec3 TexCoords;

uniform mat4 view;
uniform mat4 projection;

void main()
{
    mat4 rotView = mat4(mat3(view)); // remove translation
    vec4 pos = projection * rotView * vec4(vPos, 1.0);
    gl_Position = pos;
    TexCoords = vPos; // direction from center
}