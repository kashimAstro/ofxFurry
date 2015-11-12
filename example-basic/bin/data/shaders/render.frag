#version 330 compatibility

in vec4 vertex_color;
in vec4 dist;
const vec4 WIRE_COL = vec4(1.0,0.0,0.0,1);

void main(void) {   
   //float d = min(dist[0],min(dist[1],dist[2]));
   //float I = exp2(-2*d*d);
   //vec4 FILL_COL=vec4(vertex_color);
   //gl_FragColor = FILL_COL;
   gl_FragColor = vertex_color;	
}
