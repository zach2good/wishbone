#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 projection;
uniform vec4 srcRect;

void main()
{
	TexCoords = vertex.xy;
	
	TexCoords.x /= srcRect.x;
	TexCoords.x += (srcRect.z/srcRect.x);
	
	TexCoords.y /= srcRect.y;
	TexCoords.y += (srcRect.w/srcRect.y);

    gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
}