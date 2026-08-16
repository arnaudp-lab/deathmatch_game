#version 450 core

uniform sampler2D u_diffuse1;
uniform sampler2D u_specular;

out vec4 color;

in vec3 position;
in vec3 normal;
in vec3 tangent;
in vec3 bitangent;
in vec2 tex_coords;

void main()
{
	color = texture(u_diffuse1, tex_coords);
}