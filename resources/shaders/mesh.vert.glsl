#version 450 core

uniform mat4 u_mvp;

layout(location=0) in vec3 v_position;
layout(location=1) in vec3 v_normal;
layout(location=2) in vec3 v_tangent;
layout(location=3) in vec3 v_bitangent;
layout(location=4) in vec2 v_tex_coords;

out vec3 position;
out vec3 normal;
out vec3 tangent;
out vec3 bitangent;
out vec2 tex_coords;

void main()
{
	position = v_position; 
	normal = v_normal; 
	tangent = v_tangent; 
	bitangent = v_bitangent; 
	tex_coords = v_tex_coords;
	
	gl_Position = u_mvp * vec4(v_position, 1.0);
}