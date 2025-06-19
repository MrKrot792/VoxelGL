#version 330 core

layout (location = 0) in vec3 aPos; // position has attribute position 0

out vec3 vertexColor; // specify a color output to the fragment shader

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 color;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    vertexColor = color; // output variable to dark-red
}
