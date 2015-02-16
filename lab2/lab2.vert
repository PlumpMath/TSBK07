#version 150

in vec3 in_Position;
in vec2 inTexCoord;
uniform mat4 rotationZ;
uniform mat4 rotationX;
uniform mat4 translation;
uniform mat4 projectionMatrix;
uniform mat4 lookMatrix;
out vec4 gl_Position;
out vec2 vert_TexCoord;

void main(void)
{
	vert_TexCoord = inTexCoord;
	gl_Position = projectionMatrix * lookMatrix * translation * rotationX * rotationZ  * vec4(in_Position, 1.0);

}
