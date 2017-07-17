#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>

uniform mat4 model;
uniform mat4 projection;

void main()
{
    gl_Position = model * vec4(vertex.xy, 0.0, 1.0);
}