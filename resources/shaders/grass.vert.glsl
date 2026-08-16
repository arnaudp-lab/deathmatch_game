#version 450 core

layout(location=0) in vec3 v_position;
layout(location=1) in int v_color_id;
layout(location=2) in vec3 v_instance_pos;

out vec3 color;

uniform mat4 u_mvp;
uniform vec3 u_colors[4];

void main()
{
	color = u_colors[v_color_id];
	gl_Position = u_mvp * vec4(v_instance_pos + v_position, 1.0);
}