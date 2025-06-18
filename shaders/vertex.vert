#version 330 core

layout (location = 0) in vec3 aPos; // position has attribute position 0
layout (location = 1) in vec3 aColor;

out vec3 vertexColor; // specify a color output to the fragment shader

uniform float time;

void main()
{
    gl_Position = vec4(aPos, 1); // we give a vec3 to vec4’s constructor
    vertexColor = aColor; // output variable to dark-red
}
