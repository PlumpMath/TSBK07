#version 150

in vec2 vert_TexCoord;
in vec3 vert_normal;
in vec3 vert_surface;

uniform vec3 lightSourcesDirPosArr[4];
uniform vec3 lightSourcesColorArr[4];
uniform float specularExponent[4];
uniform bool isDirectional[4];

uniform mat4 transform;
uniform sampler2D texUnit;
uniform sampler2D maskrosen;

out vec4 out_Color;

const vec3 light = vec3(0.58, 0.58, 0.58);

void main(void){
	float shade;
	shade = clamp(dot(light, normalize(vert_normal)), 0, 1);

	vec3 reflectedLightDirection = reflect(-lightSourcesDirPosArr[2], mat3(transform) * vert_normal);
	vec3 eyeDirection = normalize(mat3(transform) * (-vert_surface));

	float specularStrength = 0.0;
	if(dot(lightSourcesDirPosArr[2], vert_normal) > 0.0) {
		specularStrength = dot(reflectedLightDirection, eyeDirection);
		specularStrength = max(specularStrength, 0.01);
		specularStrength = pow(specularStrength, specularExponent[2]);
	}

	vec3 light = specularStrength * lightSourcesColorArr[2] + shade;
	out_Color = sin(vert_surface.x) * texture(maskrosen, vert_TexCoord) * vec4(light, 1.0) +
		(1 - sin(vert_surface.x)) * texture(texUnit, vert_TexCoord) * vec4(light, 1.0);
}
