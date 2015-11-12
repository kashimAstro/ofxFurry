#include "ofMain.h"
#include "ofxKinect.h"
#include "ofxDelaunay.h"

class THKinect : public ofThread{
	public:
	ofxKinect * kinect;
	bool startData;
	int colorAlpha;
        ofMesh convertedMesh;
        ofxDelaunay del;
        ofPixels blob;
        float noiseAmount;
        int pointSkip;
        int distnect;
        int distnect2;

	void start(){
		startThread();
	}

	void stop(){
		stopThread();
	}
	
	void init(int _pointSkip = 6, int _dist=1100, int _steps=50){
	        blob.allocate(640,480,OF_IMAGE_GRAYSCALE);
		colorAlpha=255;
		pointSkip=_pointSkip;
		distnect=_dist;
		startData=true;
	}

	void kinectMesh(int i){
           ofTranslate(0, -80, 1100);
           if(i == 0)
              convertedMesh.draw();
           else
              convertedMesh.drawWireframe();
        }

	void generatedMesh(int _dist,int _dist2) {
	    del.reset();
	    unsigned char* pix = new unsigned char[640*480];
	    for(int x=0;x<640;x+=1) {
		 for(int y=0;y<480;y+=1) {
		      float distance = kinect->getDistanceAt(x, y);
		      int pIndex = x + y * 640;
		      pix[pIndex] = 0;
		      if(distance > 100 && distance < distnect) { //
			    pix[pIndex] = 255;
		      }
		 }
	    }
	    blob.setFromPixels(pix, 640,480, OF_IMAGE_GRAYSCALE);
	    int numPoints = 0;
	    for(int x=0;x<640;x+=pointSkip) {
	       for(int y=0;y<480;y+=pointSkip) {
		    int pIndex = x + 640 * y;
		    if(blob.getPixels()[pIndex]> 0) {
			ofVec3f wc = kinect->getWorldCoordinateAt(x, y);
			wc.x = x - 320.0;
			wc.y = y - 240.0;
			if(abs(wc.z) > 100 && abs(wc.z ) < distnect2) {
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
		    ofColor c = kinect->getColorAt(v.x+320.0, v.y+240.0);
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

	void update(ofxKinect *xkinect) {
		kinect = xkinect;
		if(kinect->isFrameNew() && startData) {
			start();
			startData=false;
		}
	}
        
        void setSteps(int skip){
           pointSkip=skip;
        }
        
	void setDistance(int dist=1100){
	    distnect=dist;
	}

	void setDistance2(int dist=1200){
	    distnect2=dist;
	}

    	void threadedFunction() {
        	while(isThreadRunning()) {
			if(kinect->isFrameNew()){
				generatedMesh(distnect,distnect2);
			}
		}
        }
};
