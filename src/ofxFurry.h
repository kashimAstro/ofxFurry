#include "ofMain.h"
#ifdef KINECT
#include "ofxDelaunay.h"
#include "ofxKinect.h"
#endif

class ofxFurry : public ofBaseApp {

	public:
	#ifdef KINECT
        int colorAlpha;
        ofVboMesh convertedMesh;
        ofxDelaunay del;
        ofImage blob;
        float noiseAmount;
        int pointSkip;
        int distnect;
	#endif

        float alpha;
        float hairLeng;
        ofVec3f color;
        ofShader shader;

	void initfurry(int _pointSkip = 6, int _dist=1100 ) {
	    shader.setGeometryInputType(GL_LINES);
	    shader.setGeometryOutputType(GL_TRIANGLE_STRIP);
	    shader.setGeometryOutputCount((5 + 1) * (4 + 1) * 2);
	    shader.load( "shaders/vertex.glsl", "shaders/fragment.glsl", "shaders/geom_hair.glsl");
	    printf("Max output vertices: %i\n", shader.getGeometryMaxOutputCount());
	    #ifdef KINECT
            blob.allocate(640,480,OF_IMAGE_GRAYSCALE);
	    colorAlpha=255;
	    pointSkip=_pointSkip;
	    distnect=_dist;
	    #endif
	}

	#ifdef KINECT
	void generatedMesh(ofxKinect &kinect) {
		del.reset();
		unsigned char* pix = new unsigned char[640*480];
		for(int x=0;x<640;x+=1) {
		     for(int y=0;y<480;y+=1) {
	                  float distance = kinect.getDistanceAt(x, y);
			  int pIndex = x + y * 640;
			  pix[pIndex] = 0;
			  if(distance > 100 && distance < distnect) { // 
					pix[pIndex] = 255;
			  }
		     }
		}
		blob.setFromPixels(pix, 640, 480, OF_IMAGE_GRAYSCALE);
		int numPoints = 0;
		for(int x=0;x<640;x+=pointSkip) {
		   for(int y=0;y<480;y+=pointSkip) {
			int pIndex = x + 640 * y;
			if(blob.getPixels()[pIndex]> 0) {
				ofVec3f wc = kinect.getWorldCoordinateAt(x, y);
				wc.x = x - 320.0;
		                wc.y = y - 240.0;
				if(abs(wc.z) > 100 && abs(wc.z ) < 2000) { // 
					wc.z = -wc.z;
				        wc.x += ofSignedNoise(wc.x,wc.z)*noiseAmount;
                                	wc.y += ofSignedNoise(wc.y,wc.z)*noiseAmount;
					wc.x = ofClamp(wc.x, -320,320);
					wc.y = ofClamp(wc.y, -240,240);
					del.addPoint(wc);
				}
				numPoints++;
			}
		    }
		}

		if(numPoints >0) del.triangulate();
		for(int i=0;i<del.triangleMesh.getNumVertices();i++) { del.triangleMesh.addColor(ofColor(0,0,0)); }
			for(int i=0;i<del.triangleMesh.getNumIndices()/3;i+=1) {
				ofVec3f v = del.triangleMesh.getVertex(del.triangleMesh.getIndex(i*3));
				v.x = ofClamp(v.x, -319,319);
				v.y = ofClamp(v.y, -239, 239);
				ofColor c = kinect.getColorAt(v.x+320.0, v.y+240.0);
				c.a = colorAlpha;
				del.triangleMesh.setColor(del.triangleMesh.getIndex(i*3),c);
				del.triangleMesh.setColor(del.triangleMesh.getIndex(i*3+1),c);
				del.triangleMesh.setColor(del.triangleMesh.getIndex(i*3+2),c);
			}

		convertedMesh.clear();
		for(int i=0;i<del.triangleMesh.getNumIndices()/3;i+=1) {
			int indx1 = del.triangleMesh.getIndex(i*3);
			ofVec3f p1 = del.triangleMesh.getVertex(indx1);
			int indx2 = del.triangleMesh.getIndex(i*3+1);
			ofVec3f p2 = del.triangleMesh.getVertex(indx2);
			int indx3 = del.triangleMesh.getIndex(i*3+2);
			ofVec3f p3 = del.triangleMesh.getVertex(indx3);
			ofVec3f triangleCenter = (p1+p2+p3)/3.0;
			triangleCenter.x += 320;
			triangleCenter.y += 240;
			triangleCenter.x = floor(ofClamp(triangleCenter.x, 0,640));
			triangleCenter.y = floor(ofClamp(triangleCenter.y, 0,480));
			int pixIndex = triangleCenter.x + triangleCenter.y * 640;
			if(pix[pixIndex] > 0) {
				convertedMesh.addVertex(p1);
				convertedMesh.addColor(del.triangleMesh.getColor(indx1));
				convertedMesh.addVertex(p2);
				convertedMesh.addColor(del.triangleMesh.getColor(indx2));
				convertedMesh.addVertex(p3);
				convertedMesh.addColor(del.triangleMesh.getColor(indx3));
			}
		}
		delete pix;
	}
	#endif
	
	void begin(ofEasyCam cam, ofVec3f color, float hairLeng = 2.2, float alpha = 1.f, float noise = 0.f,  bool noTassellation=true){
		glEnable(GL_DEPTH_TEST);
		shader.begin();
	        shader.setUniform1f("hairLeng",hairLeng);
		shader.setUniform1f("timex",noise );
		float tass=0.;
		if(noTassellation==true) 
		      tass = 1.;
	        shader.setUniform1f("noTass",tass);
	        shader.setUniformMatrix4f("projection",cam.getProjectionMatrix());
	        shader.setUniformMatrix4f("modelview", cam.getModelViewMatrix() );
	        shader.setUniform1f("alpha", alpha);
	        shader.setUniform3f("colored", color.x,color.y,color.z);
 	}

	#ifdef KINECT
	void kinectMesh(){
		ofTranslate(0, -80, 1100);
		convertedMesh.draw();
	}
	#endif

	void end(){
		shader.end();
		glDisable(GL_DEPTH_TEST);
	}
	#ifdef KINECT
	void drawDebug() {
		blob.draw(280,20,blob.getWidth()/3,blob.getHeight()/3);
		ofPushMatrix();
		ofTranslate(650,-250,0);
		del.draw();
		ofPopMatrix();
		ofPushMatrix();
		ofTranslate(1100,-250,0);
		convertedMesh.drawWireframe();
		ofPopMatrix();
	}
	#endif
};	
