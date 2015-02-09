#version 150

in vec3 in_Position;
in vec3 blaha;
uniform mat4 rotation;
uniform mat4 translation;
out vec4 gl_Position;
out vec3 in_colors;

void main(void)
{
	in_colors = blaha;
	gl_Position = rotation * translation * vec4(in_Position, 1.0);

}
