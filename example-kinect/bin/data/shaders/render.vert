#version 330 compatibility

out VertexAttrib {
      vec3 normal;
      vec4 color;
} vertex;

void main() {	
      gl_Position = gl_Vertex;
      vertex.normal =  gl_Normal.xyz;
      vertex.color =  vec4(1.0, 1.0, 0.0, 1.0);
}
