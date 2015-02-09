#version 150

in vec3 in_colors;
in vec2 vert_TexCoord;
out vec4 out_Color;

void main(void){
	float f = dot(in_colors, in_colors);
	out_Color = vec4(vert_TexCoord, f, 1.0);
}
