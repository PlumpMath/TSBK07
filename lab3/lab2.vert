#version 150

in vec3 in_Position;
in vec2 in_TexCoord;
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
	vec3 out_normal = vec3(mat3(transform) * in_Normal);
	shade = dot(normalize(out_normal), light);
	shade = clamp(shade, 0, 1);
	vert_shade = vec3(shade);

	vert_TexCoord = in_TexCoord;
	gl_Position = projectionMatrix * lookMatrix * transform  * vec4(in_Position, 1.0);

}
