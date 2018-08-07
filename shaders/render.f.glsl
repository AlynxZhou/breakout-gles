#version 300 es

precision mediump float;

in vec2 tex_coords;

out vec4 out_color;

uniform sampler2D image;
uniform vec4 color;

void main()
{
	out_color = color * texture(image, tex_coords);
}
