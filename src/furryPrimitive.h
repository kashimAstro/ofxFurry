#include "ofMain.h"

#define STRINGIFY(A) #A

class FurryPrimitive 
{
	public:
		ofTexture tex;
                ofBufferObject buffer;
                vector<ofMatrix4x4> matrices;
                ofVboMesh mesh,xmesh;
                ofShader shader;
		ofImage texture;
		ofVec3f arr[47];
		ofVec3f direction;
		int rangeorien;
		int rangescale;
		ofVec3f scale;
		bool noise,CustomMesh;
		float valueNoise;
		int resizedMesh;

		void setRangeOrientation(int _r){
			rangeorien = _r;
		}

		void setRangeScale(int _r){
			rangescale = _r;
		}

		void setScale(ofVec3f _s){
			scale = _s;
		}

		void setOrientation(ofVec3f _d){
			direction = _d;
		}

		void setTexture(ofImage _i){
			ofDisableArbTex();
			texture = _i;
		}

		void setNoise(float _t, bool _n){
			noise = _n;
			valueNoise = _t;
		}

		void setCustomMesh(ofMesh _m){
			mesh = _m;
			mesh.setUsage(GL_STATIC_DRAW);
			CustomMesh = true;
		}

		void setPrimitive(int prim){
			if(prim == 0)
			{
				ofConePrimitive cone;
				cone.set(35, 355, 3,3);
				mesh = cone.getMesh();
			}
			if(prim == 1)
			{
				ofBoxPrimitive box;
				box.set(35);
				mesh = box.getMesh();
			}
			if(prim == 2)
			{
				ofSpherePrimitive sph;
				sph.set(35,4);
				mesh = sph.getMesh();
			}
			if(prim == 3)
			{
				ofIcoSpherePrimitive ico;
				ico.set(35,0.5);
				mesh = ico.getMesh();
			}
			if(prim == 4)
			{
				ofCylinderPrimitive cyl;
				cyl.set(35,300);
				mesh = cyl.getMesh();
			}
			if(prim == 5)
			{
				vector<ofVec3f> points;
				for(int i = 0; i < 46; i++)
				{
					points.push_back(
						arr[i]
					);
				}
				mesh = ribbon(points,ofRandom(10,55));
			}
			if(prim == 6)
			{
				ofMesh app;
				ofConePrimitive cone;
		                app.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
                	        for(int k = 0; k < 4; k++)
	                        {
        	                        cone.set(20,100,6,6);
	                                for(int i = 0; i < cone.getMesh().getVertices().size();i++)
        	                                cone.getMesh().getVertices()[i] +=
	                                                ofVec3f(
								cone.getMesh().getVertices()[i].x,
								cone.getMesh().getVertices()[i].y+(k*200),
								cone.getMesh().getVertices()[i].z
	                                        );
	                                app.append(cone.getMesh());
        	                }
				mesh = app;
			}
			if(prim == 7)
			{
				ofMesh app;
				ofSpherePrimitive sphere;
		                app.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
                	        for(int k = 0; k < 4; k++)
	                        {
        	                        sphere.set(20,4);
	                                for(int i = 0; i < sphere.getMesh().getVertices().size();i++)
        	                                sphere.getMesh().getVertices()[i] +=
	                                                ofVec3f(
								sphere.getMesh().getVertices()[i].x,
								sphere.getMesh().getVertices()[i].y+(k*100),
								sphere.getMesh().getVertices()[i].z
	                                        );
	                                app.append(sphere.getMesh());
        	                }
				mesh = app;
			}
			if(prim == 8)
			{
				ofMesh app;
				ofCylinderPrimitive cyl;
		                app.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
                	        for(int k = 0; k < 4; k++)
	                        {
        	                        cyl.set(6,50);
	                                for(int i = 0; i < cyl.getMesh().getVertices().size();i++)
        	                                cyl.getMesh().getVertices()[i] +=
	                                                ofVec3f(
								cyl.getMesh().getVertices()[i].x,
								cyl.getMesh().getVertices()[i].y+(k*200),
								cyl.getMesh().getVertices()[i].z
	                                        );
	                                app.append(cyl.getMesh());
        	                }
				mesh = app;
			}
			if(prim == 9)
			{
				ofMesh app;
				ofIcoSpherePrimitive ico;
		                app.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
                	        for(int k = 0; k < 4; k++)
	                        {
        	                        ico.set(10,0.5);
	                                for(int i = 0; i < ico.getMesh().getVertices().size();i++)
        	                                ico.getMesh().getVertices()[i] +=
	                                                ofVec3f(
								ico.getMesh().getVertices()[i].x,
								ico.getMesh().getVertices()[i].y+(k*100),
								ico.getMesh().getVertices()[i].z
	                                        );
	                                app.append(ico.getMesh());
        	                }
				mesh = app;
			}

			if(prim == 10)
			{
				ofMesh app;
				ofIcoSpherePrimitive ico;
				ofCylinderPrimitive cyl;
		                app.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
                	        for(int k = 0; k < 4; k++)
	                        {
        	                        ico.set(10,0.5);
        	                        cyl.set(5,25);
	                                for(int i = 0; i < ico.getMesh().getVertices().size();i++)
					{
        	                                ico.getMesh().getVertices()[i] +=
	                                                ofVec3f(
								ico.getMesh().getVertices()[i].x,
								ico.getMesh().getVertices()[i].y+(k*100),
								ico.getMesh().getVertices()[i].z
	                                        );
					}
	                                for(int i = 0; i < cyl.getMesh().getVertices().size();i++)
					{
					        cyl.getMesh().getVertices()[i] +=
	                                                ofVec3f(
								cyl.getMesh().getVertices()[i].x,
								cyl.getMesh().getVertices()[i].y+(k*100),
								cyl.getMesh().getVertices()[i].z
	                                        );

					}
					if(k % 2 == 0)
		                                app.append(ico.getMesh());
					else
		                                app.append(cyl.getMesh());
        	                }
				mesh = app;
			}


			mesh.setUsage(GL_STATIC_DRAW);
                        //mesh.getTexCoords().resize(matrices.size());
                        //for(size_t i=0;i<mesh.getTexCoords().size();i++)
                        //mesh.getTexCoords()[i] = ofVec2f(i*2,i*2);
                        //mesh.getVbo().setAttributeDivisor(ofShader::TEXCOORD_ATTRIBUTE,1);
		}

		void setup(ofMesh _m){
			resizedMesh = 25;
			noise = false;
			direction = ofVec3f(-1,-2,1);
			rangeorien = 1;
			rangescale = 1;
			scale = ofVec3f(1,1,1);

			arr[0]= ofVec3f(198.704, 57.9148, 44.8024);
			arr[1]= ofVec3f(196.848, 71.8602, 55.7667);
			arr[2]= ofVec3f(196.109, 76.3665, 59.3335);
			arr[3]= ofVec3f(193.99, 87.4586, 68.1741);
			arr[4]= ofVec3f(190.945, 100.38, 78.5997);
			arr[5]= ofVec3f(187.708, 111.746, 87.91);
			arr[6]= ofVec3f(183.831, 123.272, 97.5129);
			arr[7]= ofVec3f(179.308, 134.723, 107.252);
			arr[8]= ofVec3f(174.453, 145.281, 116.447);
			arr[9]= ofVec3f(169.015, 155.5, 125.595);
			arr[10]= ofVec3f(163.225, 164.921, 134.301);
			arr[11]= ofVec3f(156.6, 174.225, 143.229);
			arr[12]= ofVec3f(150.305, 181.865, 150.882);
			arr[13]= ofVec3f(143.051, 189.451, 158.867);
			arr[14]= ofVec3f(135.323, 196.308, 166.545);
			arr[15]= ofVec3f(127.072, 202.424, 173.936);
			arr[16]= ofVec3f(118.866, 207.424, 180.568);
			arr[17]= ofVec3f(110.181, 211.671, 186.899);
			arr[18]= ofVec3f(101.12, 215.07, 192.83);
			arr[19]= ofVec3f(91.557, 217.623, 198.417);
			arr[20]= ofVec3f(81.7352, 219.23, 203.499);
			arr[21]= ofVec3f(71.5848, 219.894, 208.107);
			arr[22]= ofVec3f(61.0166, 219.585, 212.261);
			arr[23]= ofVec3f(50.7337, 218.365, 215.709);
			arr[24]= ofVec3f(40.1745, 216.22, 218.673);
			arr[25]= ofVec3f(29.1371, 213.059, 221.175);
			arr[26]= ofVec3f(18.0122, 208.962, 223.102);
			arr[27]= ofVec3f(6.87665, 203.981, 224.451);
			arr[28]= ofVec3f(-3.95082, 198.317, 225.218);
			arr[29]= ofVec3f(-15.2949, 191.539, 225.453);
			arr[30]= ofVec3f(-27.0363, 183.631, 225.087);
			arr[31]= ofVec3f(-38.1115, 175.35, 224.173);
			arr[32]= ofVec3f(-49.1613, 166.301, 222.706);
			arr[33]= ofVec3f(-60.4373, 156.257, 220.627);
			arr[34]= ofVec3f(-72.0422, 145.062, 217.857);
			arr[35]= ofVec3f(-83.2303, 133.437, 214.56);
			arr[36]= ofVec3f(-94.0446, 121.408, 210.764);
			arr[37]= ofVec3f(-104.743, 108.723, 206.387);
			arr[38]= ofVec3f(-115.09, 95.6928, 201.532);
			arr[39]= ofVec3f(-126.043, 81.042, 195.675);
			arr[40]= ofVec3f(-135.179, 68.114, 190.18);
			arr[41]= ofVec3f(-144.845, 53.6951, 183.707);
			arr[42]= ofVec3f(-154.374, 38.6841, 176.594);
			arr[43]= ofVec3f(-163.327, 23.7996, 169.171);
			arr[44]= ofVec3f(-172.113, 8.38369, 161.096);
			arr[45]= ofVec3f(-180.557, -7.27125, 152.487);

			xmesh = _m;

		        matrices.resize( xmesh.getNumVertices() );
		        buffer.allocate();
		        buffer.bind(GL_TEXTURE_BUFFER);
		        buffer.setData(matrices,GL_STREAM_DRAW);
		        tex.allocateAsBufferTexture(buffer,GL_RGBA32F);

			string vertex = STRINGIFY(
				\n#version 150\n
				uniform mat4 modelViewProjectionMatrix;
				in vec4 position;
				in vec2 texcoord;
				in vec4 instanceColor;
				uniform samplerBuffer tex;
				uniform sampler2D texture;
				out vec4 color;
				out vec2 v_texcoord;
				void main(){
				    int x = gl_InstanceID*4;
				    mat4 transformMatrix = mat4(
				        texelFetch(tex, x),
				        texelFetch(tex, x+1),
				        texelFetch(tex, x+2),
				        texelFetch(tex, x+3)
				    );
				    v_texcoord = position.xy;
				    vec4 t = texture2D(texture,texcoord);
				    color  = t ;
				    gl_Position = modelViewProjectionMatrix * transformMatrix * position;
				}
			);
			string fragment = STRINGIFY(
				\n#version 150\n
				in vec4 color;
				in vec2 v_texcoord;
				out vec4 outColor;
				void main(){
			        	outColor = color;
				}
			);
		        shader.setupShaderFromSource(GL_VERTEX_SHADER,       vertex);
		        shader.setupShaderFromSource(GL_FRAGMENT_SHADER,     fragment);
			if(ofIsGLProgrammableRenderer()){
		                shader.bindDefaults();
		        }
		        shader.linkProgram();

		        shader.begin();
		        shader.setUniformTexture("tex",tex,0);
		        shader.end();

			if(!CustomMesh)
				setPrimitive(0);
		}

		void update(ofMesh _m){
                        xmesh = _m;

		        for(size_t i=0;i<xmesh.getNumVertices();i++){
	                	ofNode node;
				ofVec3f pos;
				if(!noise)
				{
		                	pos.set(
		                	        xmesh.getVertex(i).x,
	                		        xmesh.getVertex(i).y,
	        	        	        xmesh.getVertex(i).z
					);
				}
				else
				{
					float t = (valueNoise);
				 	pos.set(
                			        xmesh.getVertex(i).x+ofNoise(t),
		               		        xmesh.getVertex(i).y+ofNoise(t),
		       	        	        xmesh.getVertex(i).z+ofNoise(t)
					);
				}
				ofVec3f rot(
					xmesh.getVertex(i).x*direction.x,
					xmesh.getVertex(i).y*direction.y,
					xmesh.getVertex(i).z*direction.z
				);
				pos *= resizedMesh;
		                node.setPosition(pos);
		                if(i % rangeorien == 0) node.setOrientation(rot);
				if(i % rangescale == 0) node.setScale(scale);
                		matrices[i] = node.getLocalTransformMatrix();
		        }
		        buffer.updateData(0,matrices);
		}
		
		ofMesh getMeshResized(){
			ofMesh tmp = xmesh;	
                        for(int i = 0; i < tmp.getVertices().size();i++)
			{
				//if(!noise)
				//{
			        	tmp.getVertices()[i] +=
        	                        ofVec3f(
						tmp.getVertices()[i].x,
						tmp.getVertices()[i].y,
						tmp.getVertices()[i].z
		                               )*(resizedMesh-1);

				/*}
				else
				{
					float t = (valueNoise + i);
					tmp.getVertices()[i] +=
        	                        ofVec3f(
						tmp.getVertices()[i].x * ofNoise(t),
						tmp.getVertices()[i].y * ofNoise(t),
						tmp.getVertices()[i].z * ofNoise(t)
		                               )*(resizedMesh-1);
				}*/
			}
			return tmp;
		}

		void draw(ofPolyRenderMode type){
			shader.begin();
			shader.setUniformTexture("texture",texture.getTexture(),1);
			mesh.drawInstanced(type,matrices.size());
			shader.end();
		}

		ofMesh ribbon(vector<ofVec3f> points, float _thickness){
		    ofVboMesh mesh;
		    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
                    float thickness = _thickness;
		    
		    for(unsigned int i = 1; i < points.size(); i++){
			ofVec3f thisPoint = points[i-1];
			ofVec3f nextPoint = points[i];
			ofVec3f direction = (nextPoint - thisPoint);
			ofVec3f unitDirection = direction.normalized();
			ofVec3f toTheLeft = unitDirection.getRotated(90, ofVec3f(0, 1, 1));
			ofVec3f toTheRight = unitDirection.getRotated(-90, ofVec3f(0, 1, 1));
			ofVec3f leftPoint = thisPoint+toTheLeft * thickness;
			ofVec3f rightPoint = thisPoint+toTheRight * thickness;
			mesh.addVertex(ofVec3f(leftPoint.x, leftPoint.y, leftPoint.z));
			mesh.addVertex(ofVec3f(rightPoint.x, rightPoint.y, rightPoint.z));
		    }
		    return mesh;
		}

};
