#version 150

uniform float color;
uniform float alpha;
uniform vec3 colored;

in vec3 fcolor;
in float stime;
in vec3 weight;

out vec4 frag_color;

const float DISCARD_AT = .1;
const float BACKGROUND_AT = 0.05;
const float BACKGROUND = 1.0;

void main() {
	float mindist = min(weight.r, min(weight.g, weight.b));
	if (mindist > DISCARD_AT) discard;
	float intensity = mindist > BACKGROUND_AT ? BACKGROUND : color;
	frag_color += vec4(vec3(intensity), 1.0);
	frag_color = vec4(vec3(fcolor.r*colored.r,fcolor.g*colored.g,fcolor.b*colored.b), alpha);
}
