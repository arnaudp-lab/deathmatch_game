#version 450 core

out vec4 color;

in vec3 v_coords;

uniform samplerCube u_skybox_texture;

void main()
{
	color = texture(u_skybox_texture, v_coords);
}