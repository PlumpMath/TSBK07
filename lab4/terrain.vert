#version 150

in vec3 inPosition;
in vec3 inNormal;
in vec2 inTexCoord;

// NY
uniform mat4 projMatrix;
uniform mat4 mdlMatrix;

out vec2 vert_texCoord;
out vec3 vert_normal;
out vec3 vert_surface;
out vec4 world_position;

void main(void)
{
	vert_normal = inNormal;
	vert_surface = inPosition;
	vert_texCoord = inTexCoord;
	gl_Position = projMatrix * mdlMatrix * vec4(inPosition, 1.0);
	world_position = gl_Position;
}
