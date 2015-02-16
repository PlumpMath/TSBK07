#version 150

in vec3 in_Position;
in vec2 inTexCoord;
in vec3 in_Normal;
uniform mat4 transform;
uniform mat4 projectionMatrix;
uniform mat4 lookMatrix;
out vec4 gl_Position;
out vec2 vert_TexCoord;
out vec3 vert_shade;

const vec3 light = vec3(0.58, 0.58, 0.58);

void main(void)
{
	float shade;
	shade = dot(normalize(in_Normal), light);
	shade = clamp(shade, 0, 1);
	vert_shade = vec3(shade);

	vert_TexCoord = inTexCoord;
	gl_Position = projectionMatrix * lookMatrix * transform  * vec4(in_Position, 1.0);

}
