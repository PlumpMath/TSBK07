#version 150

in vec2 vert_texCoord;
in vec3 vert_normal;
in vec3 vert_surface;
uniform sampler2D maskrosen;
uniform sampler2D dirt;
out vec4 outColor;

const vec3 light = vec3(0.58, -0.58, 0.58);

void main(void)
{
	float shade;
	shade = clamp(dot(light, normalize(vert_normal)), 0, 1);

if (vert_surface.y > 1 && vert_surface.y < 10 )
{
outColor = texture(maskrosen, vert_texCoord)*shade;
}
else
{
outColor = texture(dirt, vert_texCoord)*shade;
}

}
