#version 450 core

layout (location = 0) in vec3 v_position;

out vec3 v_coords;

uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
    v_coords = v_position;
    gl_Position = u_projection * u_view * vec4(v_position, 1.0);
}