#version 330 core

layout (location = 0) in vec3 aPos; // position has attribute position 0
out vec4 vertexColor; // specify a color output to the fragment shader

uniform float time;

void main()
{
    gl_Position = vec4(aPos, 1.0); // we give a vec3 to vec4’s constructor
    vertexColor = vec4(cos(time * 1), cos(time * 2), cos(time * 3), 1); // output variable to dark-red
}
