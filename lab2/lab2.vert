#version 150

in vec3 in_Position;
in vec3 in_Normal;
in vec2 inTexCoord;
uniform mat4 rotationZ;
uniform mat4 rotationX;
uniform mat4 translation;
out vec4 gl_Position;
out vec3 in_colors;
out vec2 vert_TexCoord;

void main(void)
{
	vert_TexCoord = inTexCoord;
	in_colors = in_Normal;
	gl_Position = rotationX * rotationZ * translation * vec4(in_Position, 1.0);

}
