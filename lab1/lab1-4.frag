#version 150

in vec3 in_colors;
out vec4 out_Color;

void main(void){
	out_Color = vec4(in_colors, 1.0);
}
