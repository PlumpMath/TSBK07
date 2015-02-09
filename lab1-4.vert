#version 150

in  vec3 in_Position;
uniform mat4 rotation;
uniform mat4 translation;
out vec4 gl_Position;
out vec3 in_color;

void main(void)
{
	gl_Position = rotation * translation * vec4(in_Position, 1.0);
	
}
