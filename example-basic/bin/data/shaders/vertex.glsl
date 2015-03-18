#version 150

in vec3 position;
in vec3 normal;
out vec3 gnormal;

void main() {
  gl_Position = vec4(position, 1.0);
  gnormal = normal;
}
