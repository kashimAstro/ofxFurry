#include "ofMain.h"
#include "glsl.h"

vector<string> glsl::getFurry() {
    vector<string> storage;

    string computeShader = STRINGIFY(
          struct Spring{
             vec4 pos;
             vec4 vel;
             vec4 color;
          };         
          layout(std140, binding=0) buffer spring{ Spring s[]; };
          layout(std140, binding=1) buffer springBack{ Spring s2[]; };
          layout(std140, binding=2) buffer indices{ uint idx[]; };
          layout(local_size_x = 1024, local_size_y = 1, local_size_z = 1) in;
          void main(){
             vec3 sp = s[gl_GlobalInvocationID.x].pos.xyz;
             vec3 sp2 = s2[gl_GlobalInvocationID.x].pos.xyz;             
          }
    );
    
    string helper = STRINGIFY(
	\n#version 330 compatibility\n
        \n#define VERT 3\n
	\n#define HALF_PI  1.57079632679489661923\n
	\n#define PI       3.14159265358979323846\n
	\n#define TWO_PI   6.28318530717958647693\n

	float map( float value, float inputMin, float inputMax, float outputMin, float outputMax ) { return ((value - inputMin) / (inputMax - inputMin) * (outputMax - outputMin) + outputMin); }
	float mapClamped( float value, float inputMin, float inputMax, float outputMin, float outputMax ) { return clamp( ((value - inputMin) / (inputMax - inputMin) * (outputMax - outputMin) + outputMin),    outputMin, outputMax ); }
	vec3  map( vec3 value, vec3 inputMin, vec3 inputMax, vec3 outputMin, vec3 outputMax ) { return ((value - inputMin) / (inputMax - inputMin) * (outputMax - outputMin) + outputMin); }
	float stepInOut( float _edge1, float _edge2, float _val ) { return step(_edge1, _val) - step(_edge2,_val); }
	float linearStep( float _edge0, float _edge1, float _t ) { return clamp( (_t - _edge0)/(_edge1 - _edge0), 0.0, 1.0); }
	float linearStepInOut( float _low0, float _high0, float _high1, float _low1, float _t ) { return linearStep( _low0, _high0, _t ) * (1.0f - linearStep( _high1, _low1, _t )); }
	float smoothStepInOut( float _low0, float _high0, float _high1, float _low1, float _t ) { return smoothstep( _low0, _high0, _t ) * (1.0 - smoothstep( _high1, _low1, _t )); }
	float mod289(float x) { return x - floor(x * (1.0 / 289.0)) * 289.0; }
	vec2 mod289(vec2 x)   { return x - floor(x * (1.0 / 289.0)) * 289.0; }
	vec3 mod289(vec3 x)   { return x - floor(x * (1.0 / 289.0)) * 289.0; }
	vec4 mod289(vec4 x)   { return x - floor(x * (1.0 / 289.0)) * 289.0; }
	float rand(vec2 co) { return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453); }
	float permute(float x) { return mod289(((x*34.0)+1.0)*x); }
	vec3 permute(vec3 x)   { return mod289(((x*34.0)+1.0)*x); }
	vec4 permute(vec4 x)   { return mod289(((x*34.0)+1.0)*x); }
	float taylorInvSqrt(float r) { return 1.79284291400159 - 0.85373472095314 * r; }
	vec4 taylorInvSqrt(vec4 r)   { return 1.79284291400159 - 0.85373472095314 * r; }
	mat4 makeLookAt(vec3 eye, vec3 center, vec3 up){
		mat4 M;
		vec3 zaxis = normalize(eye - center);
		vec3 xaxis = normalize( cross(up, zaxis) );
		vec3 yaxis = cross(zaxis,xaxis);

		M[0] = vec4(xaxis,0);
		M[1] = vec4(yaxis,0);
		M[2] = vec4(zaxis,0);
		M[3] = vec4(eye,1);

		return M;
	}
	mat4 rotationMatrix(vec3 axis, float angle){
		axis = normalize(axis);
		float s = sin(angle);
		float c = cos(angle);
		float oc = 1.0 - c;

		return mat4(oc * axis.x * axis.x + c,           oc * axis.x * axis.y - axis.z * s,  oc * axis.z * axis.x + axis.y * s,  0.0,
					oc * axis.x * axis.y + axis.z * s,  oc * axis.y * axis.y + c,           oc * axis.y * axis.z - axis.x * s,  0.0,
					oc * axis.z * axis.x - axis.y * s,  oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c,           0.0,
					0.0,                                0.0,                                0.0,                                1.0);
	}
	vec3 randomPointOnSphere( vec3 _random ){
		float lambda = _random.x;
		float u = map( _random.y, 0.0, 1.0, -1.0, 1.0 );
		float phi = _random.z * (2.0 * PI );

		vec3 p;
		p.x = pow(lambda, 1.0/3.0) * sqrt(1.0 - u * u) * cos(phi);
		p.y = pow(lambda, 1.0/3.0) * sqrt(1.0 - u * u) * sin(phi);
		p.z = pow(lambda, 1.0/3.0) * u;

		return p;
	}
	float pulseSquare( float _t, float _frequency, float _width )
	{
		return 1.0 - step( _width, mod( _t, _frequency ) );
	}
	float pulseTriangle( float _t, float _frequency, float _width )
	{
		float triangleT = mod( _t, _frequency ) / _width * 2.0;
		return (1.0 - abs(mod(triangleT,2.0) - 1.0)) * pulseSquare( _t, _frequency, _width );
	}
	float pulseLineDownUp( float _t, float _frequency, float _width )
	{
		float tmpVal = mod( _t, _frequency ) / _width;
		return tmpVal * (1.0 - step( 1.0, tmpVal ));
	}
	float pulseLineUpDown( float _t, float _frequency, float _width )
	{
		float tmpVal = 1 - (mod( _t, _frequency ) / _width);
		return clamp( tmpVal * (1 - step( 1.0, tmpVal )), 0, 1);
	}
	float pulseSawTooth( float _t, float _frequency, float _width )
	{
		float tmpVal = 1 - (mod( _t, _frequency ) / _width);
		return clamp( tmpVal * (1.0 - step( 1.0, tmpVal )), 0.0, 1.0);
	}
	float pulseSine( float _t, float _frequency, float _width )
	{
		float tmpVal = clamp( (mod( _t, _frequency ) / _width), 0.0, 1.0);
		return sin(tmpVal * PI);
	}
	float pulseSmoothStep( float _t, float _frequency, float _x0, float _x1, float _x2, float _x3 )
	{
		float tmpVal = mod( _t, _frequency );
		return smoothStepInOut( _x0, _x1, _x2, _x3, tmpVal ) ;
	}
	float pulseLinearStep( float _t, float _frequency, float _x0, float _x1, float _x2, float _x3 )
	{
		float tmpVal = mod( _t, _frequency );
		return linearStepInOut( _x0, _x1, _x2, _x3, tmpVal ) ;
	}
	vec3 opTwistX( vec3 _p, float _angPerUnit )
	{
		float c = cos( _angPerUnit * _p.x);
		float s = sin( _angPerUnit * _p.x);
		mat2  m = mat2(c,-s,s,c);
		return vec3( _p.x, m * _p.yz );
	}
	vec3 opTwistY( vec3 _p, float _angPerUnit )
	{
		float c = cos( _angPerUnit * _p.y);
		float s = sin( _angPerUnit * _p.y);
		mat2  m = mat2(c,-s,s,c);

		vec2 rotXZ = m * _p.xz;

		return vec3( rotXZ.x, _p.y, rotXZ.y );
	}
	vec3 opTwistZ( vec3 _p, float _angPerUnit )
	{
		float c = cos( _angPerUnit * _p.z);
		float s = sin( _angPerUnit * _p.z);
		mat2  m = mat2(c,-s,s,c);

		vec2 rotXY = m * _p.xy;

		return vec3( rotXY.x, rotXY.y, _p.z );
	}
	float CatmullRom( float u, float x0, float x1, float x2, float x3 )
	{
		float u2 = u * u;
		float u3 = u2 * u;
		return ((2 * x1) +
				(-x0 + x2) * u +
				(2*x0 - 5*x1 + 4*x2 - x3) * u2 +
				(-x0 + 3*x1 - 3*x2 + x3) * u3) * 0.5;
	}
	float cubicPulse( float c, float w, float x )
	{
		x = abs(x - c);
		if( x>w ) return 0.0;
		x /= w;
		return 1.0 - x*x*(3.0-2.0*x);
	}
	float expStep( float x, float k, float n )
	{
		return exp( -k*pow(x,n) );
	}
	float parabola( float x, float k )
	{
		return pow( 4.0*x*(1.0-x), k );
	}
	float pcurve( float x, float a, float b )
	{
		float k = pow(a+b,a+b) / (pow(a,a)*pow(b,b));
		return k * pow( x, a ) * pow( 1.0-x, b );
	}
	float impulse( float k, float x )
	{
		float h = k*x;
		return h*exp(1.0-h);
	}
	float snoise(vec2 v) {
	  const vec4 C = vec4(0.211324865405187,  // (3.0-sqrt(3.0))/6.0
			      0.366025403784439,  // 0.5*(sqrt(3.0)-1.0)
			     -0.577350269189626,  // -1.0 + 2.0 * C.x
			      0.024390243902439); // 1.0 / 41.0
	  vec2 i  = floor(v + dot(v, C.yy) );
	  vec2 x0 = v -   i + dot(i, C.xx);
	  vec2 i1;
	  i1.x = step( x0.y, x0.x ); // x0.x > x0.y ? 1.0 : 0.0
	  i1.y = 1.0 - i1.x;
	  i1 = (x0.x > x0.y) ? vec2(1.0, 0.0) : vec2(0.0, 1.0);
	  x0 = x0 - 0.0 + 0.0 * C.xx ;
	  //x1 = x0 - i1 + 1.0 * C.xx ;
	  //x2 = x0 - 1.0 + 2.0 * C.xx ;
	  vec4 x12 = x0.xyxy + C.xxzz;
	  x12.xy -= i1;
	  i = mod289(i);
	  vec3 p = permute( permute( i.y + vec3(0.0, i1.y, 1.0 )) + i.x + vec3(0.0, i1.x, 1.0 ));
	  vec3 m = max(0.5 - vec3(dot(x0,x0), dot(x12.xy,x12.xy), dot(x12.zw,x12.zw)), 0.0);
	  m = m*m ;
	  m = m*m ;
	  vec3 x = 2.0 * fract(p * C.www) - 1.0;
	  vec3 h = abs(x) - 0.5;
	  vec3 ox = floor(x + 0.5);
	  vec3 a0 = x - ox;
	  m *= 1.79284291400159 - 0.85373472095314 * ( a0*a0 + h*h );
	  vec3 g;
	  g.x  = a0.x  * x0.x  + h.x  * x0.y;
	  g.yz = a0.yz * x12.xz + h.yz * x12.yw;
	  return 130.0 * dot(m, g);
	}
    );
 
    string vertexShader = STRINGIFY(
	\n#version 330 compatibility\n
	in vec2 texCoord;

	out VertexAttrib {
	      vec3 normal;
	      vec4 color;
	      vec2 texCoord;
	} vertex;
	void main() {
	      gl_Position      = gl_Vertex;
	      vertex.normal    = gl_Normal.xyz;
	      vertex.color     = vec4(1.0, 1.0, 0.0, 1.0);
	      vertex.texCoord  = texCoord; 
	}
    );

    string fragmentShader = STRINGIFY(
	\n#version 330 compatibility\n
	uniform sampler2D texture;
	uniform int NOTex;
	in vec4 vertex_color;
	in vec4 dist;
	in vec2 texCoordOut;
	const vec4 WIRE_COL = vec4(1.0,0.0,0.0,1);
	void main(void) {
	   //float d = min(dist[0],min(dist[1],dist[2]));
	   //float I = exp2(-2*d*d);
	   //vec4 FILL_COL=vec4(vertex_color);
	   //gl_FragColor = FILL_COL;
	   if(NOTex == 1){
		vec4 tt = texture2D(texture,texCoordOut);
	        gl_FragColor = tt * vertex_color;
	   }
	   else{
	        gl_FragColor = vertex_color;
	   }
	}
    );

    string geometryShader = STRINGIFY(
	layout(triangles) in;
	layout(triangle_strip, max_vertices=6) out;
	uniform mat4 viewMatrix;
	uniform mat4 projectionMatrix;
	uniform mat4 modelMatrix;
	uniform float time;
	uniform float hairLeng;
	uniform vec3 colors;
	uniform int polygonTypes;
	uniform vec2 collisionCoord;

	in VertexAttrib {
	      vec3 normal;
	      vec4 color;
	      vec2 texCoord;
	} vertex[];

	out VertexData {
	    vec2 texCoord;
	    vec3 normal;
	} VertexOut;

	out vec4 vertex_color;
	out vec3 dist;

        vec3 quaternionRotation(vec3 original, float angle, vec3 axis) {
           normalize(axis);
           float hcos = cos(angle / 2);
           float hsin = sin(angle / 2);
           float q10 = hcos;
           float q11 = axis.x * hsin;
           float q12 = axis.y * hsin;
           float q13 = axis.z * hsin;  
           float q20 = hcos;
           float q21 = -axis.x * hsin;
           float q22 = -axis.y * hsin;
           float q23 = -axis.z * hsin;
           float qo0 = 0;
           float qo1 = original.x;
           float qo2 = original.y;
           float qo3 = original.z;
           float qt0 = q10 * qo0 - q11 * qo1 - q12 * qo2 - q13 * qo3;
           float qt1 = q10 * qo1 + q11 * qo0 + q12 * qo3 - q13 * qo2;
           float qt2 = q10 * qo2 - q11 * qo3 + q12 * qo0 + q13 * qo1;
           float qt3 = q10 * qo3 + q11 * qo2 - q12 * qo1 + q13 * qo0;
           float qe0 = qt0 * q20 - qt1 * q21 - qt2 * q22 - qt3 * q23;
           float qe1 = qt0 * q21 + qt1 * q20 + qt2 * q23 - qt3 * q22;
           float qe2 = qt0 * q22 - qt1 * q23 + qt2 * q20 + qt3 * q21;
           float qe3 = qt0 * q23 + qt1 * q22 - qt2 * q21 + qt3 * q20;
           return vec3(qe1, qe2, qe3);
        }

	void polygonA(mat4 projectionMatrix, mat4 modelViewMatrix){
	      vec3 a = vec3(gl_in[1].gl_Position - gl_in[0].gl_Position);
	      vec3 b = vec3(gl_in[2].gl_Position - gl_in[0].gl_Position);
	      vec3 center = vec3(gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position) / 3.0;
	      vec3 normal = normalize(cross(b, a));
	      float t = hairLeng / float(VERT);

	      for(int i=0; i<VERT; i++) {
		 vertex_color = vec4(colors.x,colors.y,colors.z, 1.0);
		 vec3 position = normal * map( t, 0., 1., 1.0, 500. ) + center;
		 position.x += snoise(vec2(.6f*position.x,.2f*position.y) * time);
		 position.y += snoise(vec2(.4f*position.y,.4f*position.z) * time);
		 position.z += snoise(vec2(.2f*position.x,.6f*position.y) * time);
		 VertexOut.texCoord = vertex[i].texCoord; 
		 gl_Position = projectionMatrix * modelViewMatrix * vec4(position,1.0);
		 EmitVertex();
	      }
	}

	void polygonB(mat4 projectionMatrix, mat4 modelViewMatrix){
		float xtime = 0.3 + time;
		vec3 lightDir = vec3(1.f,0.5,1.f);
		vec3 p0 = vec3(gl_in[0].gl_Position);
                vec3 p1 = vec3(gl_in[1].gl_Position);
		vec3 up = vec3(0, 0, 1); 
		vec3 dir = normalize(cross(p1, p0));
		vec3 right = normalize(cross(dir, up)); 
		vec3 norm = cross(right, dir);
		float fColMult = abs(dot(norm, lightDir));
		vec4 colMult = vec4(fColMult, fColMult, fColMult, 1.0);
		right *= hairLeng*55.5f;
		VertexOut.texCoord = vertex[0].texCoord; 
		gl_Position = projectionMatrix * modelViewMatrix * vec4(p0 - right, 1.0) * xtime;
		vertex_color = vec4(colors.x,colors.y,colors.z, 1.0);
		EmitVertex();
		VertexOut.texCoord = vertex[1].texCoord; 
		gl_Position = projectionMatrix * modelViewMatrix * vec4(p0 + right, 1.0) * xtime;
		vertex_color = vec4(colors.x-0.1,colors.y-0.1,colors.z-0.1, 1.0);
		EmitVertex();
		VertexOut.texCoord = vertex[2].texCoord; 
		gl_Position = projectionMatrix * modelViewMatrix * vec4(p1 - right, 1.0) * xtime;
		vertex_color = vec4(colors.x-0.15,colors.y-0.15,colors.z-0.15, 1.0);
		EmitVertex();
//		VertexOut.texCoord = vertex[3].texCoord; 
		gl_Position = projectionMatrix * modelViewMatrix * vec4(p1 + right, 1.0) * xtime;
		vertex_color = vec4(colors.x-0.2,colors.y-0.2,colors.z-0.2, 1.0);
		EmitVertex();
	}

	void polygonC(mat4 projectionMatrix, mat4 modelViewMatrix){
	        float radius = hairLeng*55.5f;
		vec3 p0 = gl_in[0].gl_Position.xyz;
		vec3 p1 = gl_in[1].gl_Position.xyz;
		vec3 up = vec3(0, 0, 1);
		vec3 dir = normalize(p1 - p0);
		vec3 right = normalize(cross(dir, up));
		vec3 norm = cross(right, dir);
		vec3 center = (p0 +p1) / 2.0;
		float len = distance(p0, p1);
		int hslices = 5;
		int vslices = 4;
		vec3 d;
		vec3 n;
		if (len > 190.0) 
		{
			len = (20.0 - len) / 5.0 * 5.0;
		}
		for (int i = 0; i < hslices; i ++)
		{
			float vTheta0 = PI / hslices * i - PI / 2;
			float cosV0 = cos(vTheta0);
			float sinV0 = sin(vTheta0);
			float vTheta1 = PI / hslices * (i + 1) - PI / 2;
			float cosV1 = cos(vTheta1);
			float sinV1 = sin(vTheta1);
			vec3 c0 = center + dir * len / 2 * sinV0;
			vec3 c1 = center + dir * len / 2 * sinV1;
			vec3 r0 = right * cosV0;
			vec3 r1 = right * cosV1;
			vec3 normal;
			for (int j = 0; j <= vslices; j ++) {
				d = quaternionRotation(r0, TWO_PI * j / vslices, dir);
				gl_Position = projectionMatrix * modelViewMatrix * vec4(c0 + d * radius, 1.0);
				normal = normalize(d + normalize(c0) / 2.0);
				vertex_color = vec4(colors.x,colors.y,colors.z, 1.0);
//				VertexOut.texCoord = vertex[j].texCoord;
				EmitVertex();

				d = quaternionRotation(r1, TWO_PI * j / vslices, dir);
				gl_Position = projectionMatrix * modelViewMatrix * vec4(c1 + d * radius, 1.0);
				normal = normalize(d + normalize(c1) / 2.0);
				vertex_color = vec4(colors.x-0.1,colors.y-0.1,colors.z-0.1, 1.0);
				EmitVertex();
			}
		}
	}	
	void polygonD(mat4 projectionMatrix, mat4 modelViewMatrix){
	    float bbWidth=0.5;
	    float bbHeight=1.0;
	    float ctime=time+2.5;
	    float spriteOffset=0.1;
	    vec3 pos = gl_in[0].gl_Position.xyz;
	    vec3 p0 = gl_in[0].gl_Position.xyz;
            vec3 p1 = gl_in[1].gl_Position.xyz;
            vec3 up = vec3(0, 0, 1);
            vec3 dir = normalize(p1 - p0);
            vec3 right = normalize(cross(dir, up));
            vec3 d;
	    vec3 toCamera = dir; 
	    right*=bbWidth;
	    up *= bbHeight * hairLeng;
	    pos -= (right * 0.5);
	    pos.z=gl_in[0].gl_Position.z;

            d = quaternionRotation(pos, TWO_PI * hairLeng, dir);
	    gl_Position = projectionMatrix * modelViewMatrix * vec4(p0 + d * hairLeng, 1.0);
            vertex_color = vec4(colors.x,colors.y,colors.z, 1.0);
	    EmitVertex();

	    pos.y += 1.0;
            d = quaternionRotation(pos, TWO_PI * hairLeng, dir);
	    gl_Position = projectionMatrix * modelViewMatrix * vec4(p0 + d * hairLeng, 1.0);
            vertex_color = vec4(colors.x-0.1,colors.y-0.1,colors.z-0.1, 1.0);
	    EmitVertex();

	    pos.y -= 1.0;
	    pos += right;
            d = quaternionRotation(pos, TWO_PI * hairLeng, dir);
	    gl_Position = projectionMatrix * modelViewMatrix * vec4(p1 + d * hairLeng, 1.0);
            vertex_color = vec4(colors.x-0.15,colors.y-0.15,colors.z-0.15, 1.0);
	    EmitVertex();

	    pos.y += 1.0;
            d = quaternionRotation(pos, TWO_PI * hairLeng, dir);
	    gl_Position = projectionMatrix * modelViewMatrix * vec4(p1 + d * hairLeng, 1.0);
            vertex_color = vec4(colors.x-0.2,colors.y-0.2,colors.z-0.2, 1.0);
	    EmitVertex();
	}

	void polygonE(mat4 projectionMatrix, mat4 modelViewMatrix){
		float SPEED = 5.0;
		float OFFSET = 25.0;
		float xtime = 0.004 + time;
		float radius  = hairLeng *55.5f* xtime;
		vec3 a = vec3(gl_in[1].gl_Position - gl_in[0].gl_Position);
		vec3 b = vec3(gl_in[2].gl_Position - gl_in[0].gl_Position);
		vec3 center = vec3(gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position) / 3.0;
		vec3 normal = normalize(cross(b, a));
                for(int j = 0; j < gl_in.length(); j++) {
		    vec3 newVertex;
		    newVertex = normal * cos(time * SPEED + gl_in[j].gl_Position.x) *radius* OFFSET + vec3(gl_in[j].gl_Position.xyz);
		    gl_Position = projectionMatrix * modelViewMatrix * vec4(newVertex, 1.0);
	            vertex_color = vec4(colors.x,colors.y,colors.z, 1.0);
		    EmitVertex();
		}
	}
	void polygonF(mat4 projectionMatrix, mat4 modelViewMatrix){
		vec3 a = vec3(gl_in[1].gl_Position - gl_in[0].gl_Position);
                vec3 b = vec3(gl_in[2].gl_Position - gl_in[0].gl_Position);
                vec3 center = vec3(gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position) / 3.0;
                vec3 normal = normalize(cross(b, a));
		float xtime = 0.004 + time;
		float radius  = hairLeng *55.5f* xtime;
	        for(int j = 0; j < gl_in.length(); j++) {
		    vec3 newVertex;
		    newVertex = center * normal * cos(xtime * TWO_PI + gl_in[j].gl_Position.x) * radius * PI + vec3(gl_in[j].gl_Position.xyz);
		    gl_Position = projectionMatrix * modelViewMatrix * vec4(newVertex, 1.0);
	            vertex_color = vec4(colors.x,colors.y,colors.z, 1.0);
		    EmitVertex();
		}
	}

	void main() {
	   mat4 modelViewMatrix = viewMatrix * modelMatrix;
	   mat4 viewProjectionMatrix = projectionMatrix * viewMatrix;

	   for(int i=0; i<VERT; i++) {
	      vertex_color  = vec4(colors.x*snoise(vec2(colors.xy)),colors.y*snoise(vec2(colors.xy)),colors.z*snoise(vec2(colors.xy)),1.0);
	      vec4 view_pos = modelViewMatrix * gl_in[i].gl_Position;
	      gl_Position = projectionMatrix * view_pos;
	      EmitVertex();
	   }

	   if(polygonTypes == 0){
	      polygonA(projectionMatrix,modelViewMatrix);
	   }

	   if(polygonTypes == 1){
	      polygonB(projectionMatrix,modelViewMatrix);
	   }

	   if(polygonTypes == 2){
	      polygonC(projectionMatrix,modelViewMatrix);
	   }

	   if(polygonTypes == 3){
              polygonD(projectionMatrix,modelViewMatrix);
	   }
           
	   if(polygonTypes == 4){
              polygonE(projectionMatrix,modelViewMatrix);
	   }

           if(polygonTypes == 5){
              polygonF(projectionMatrix,modelViewMatrix);
	   }

	   EndPrimitive();
	}
    );

    storage.push_back(vertexShader);
    storage.push_back(fragmentShader);
    storage.push_back(helper+"\n"+geometryShader);
    //compute.setupShaderFromFile(GL_COMPUTE_SHADER,computeShader);
    //compute.linkProgram();
    return storage;
}
