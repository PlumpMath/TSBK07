#version 150

in vec2 vert_texCoord;
in vec3 vert_normal;
in vec3 vert_surface;
in vec4 world_position;

uniform sampler2D maskrosen;
uniform sampler2D dirt;
out vec4 outColor;

const vec3 light = vec3(0.58, -0.58, 0.58);

void main(void)
{

	float shade;
	shade = clamp(dot(light, normalize(vert_normal)), 0, 1);

	if (vert_normal.y < -0.7 ) {
		outColor = texture(maskrosen, vert_texCoord)*shade;
	}
	else {
		outColor = texture(dirt, vert_texCoord)*shade;
	}
	if(vert_surface.x < 0.5)
		outColor = vec4(1, 0, 0, 0);
	if(vert_surface.z < 0.5)
		outColor = vec4(0, 1, 0, 0);

}
