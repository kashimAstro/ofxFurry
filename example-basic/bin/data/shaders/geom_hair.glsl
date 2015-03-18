#version 150

#define N 9 

layout(triangles) in;
layout(line_strip) out;
layout(max_vertices = N) out;

const float NSTEPS = N;

uniform float hairLeng;
uniform float time;
uniform float timex;
uniform float noTass;

uniform mat4 projection;
uniform mat4 modelview;
uniform vec4 radius=vec4(1.);

out float stime;
out vec3 fcolor;
out vec3 weight;


void main() {
	  stime=time;
	  vec3 a = vec3(gl_in[1].gl_Position - gl_in[0].gl_Position);
	  vec3 b = vec3(gl_in[2].gl_Position - gl_in[0].gl_Position);

	  vec3 center = vec3(gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position) / 3.0;
	  vec3 normal = normalize(cross(b, a));

	  float delta = hairLeng / float(NSTEPS);
	  float t = delta;

	  for (int j = 0; j < NSTEPS; ++j) {

              fcolor = vec3(t / hairLeng);
	      vec3 position = normal * t + center;

	      position.x += -.2  * timex;
	      position.y += -.9  * t * timex/2.;
	      position.z += -1.8 * t * timex/2.;

	      gl_Position = projection * modelview * vec4(position, 1.0);
	      EmitVertex();

	      if(noTass == 1.0){
		      weight = vec3(1.0, 0.0, 0.0);
		      gl_Position = projection * modelview * gl_in[0].gl_Position * radius;
		      EmitVertex();

		      weight = vec3(0.0, 1.0, 0.0);
		      gl_Position = projection * modelview * gl_in[1].gl_Position * radius;
		      EmitVertex();

		      weight = vec3(0.0, 0.0, 1.0);
		      gl_Position = projection * modelview * gl_in[2].gl_Position * radius;
		      EmitVertex();
	      }
	      
	      t += delta;
	  }
	  EndPrimitive();
}
