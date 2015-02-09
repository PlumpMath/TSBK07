#version 150

in vec3 in_Position;
in vec3 blaha;
uniform mat4 rotationZ;
uniform mat4 rotationX;
uniform mat4 translation;
out vec4 gl_Position;
out vec3 in_colors;

void main(void)
{
	in_colors = blaha;
	gl_Position = rotationX * rotationZ * translation * vec4(in_Position, 1.0);

}
