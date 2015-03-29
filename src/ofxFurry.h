#ifndef _OFXFURRY
#define _OFXFURRY

#include "ofMain.h"

#define KINECT // comment not use kinect

#if defined(KINECT)
    #include "ofxDelaunay.h"
    #include "ofxKinect.h"
#endif

#define STRINGIFY(A) #A

class ofxFurry : public ofBaseApp {

	public:
        #if defined(KINECT)
        int colorAlpha;
        ofVboMesh convertedMesh;
        ofxDelaunay del;
        ofImage blob;
        float noiseAmount;
        int pointSkip;
        int distnect;
	int distnect2;
        #endif // KINECT

        float alpha;
        float hairLeng;
        ofVec3f color;
        ofShader shader;

        void initfurry(int _pointSkip = 6, int _dist=1100, int _steps=50 );
        void begin(ofEasyCam cam, ofVec3f translate, ofVec3f color, float hairLeng = 2.2, float alpha = 1.f, float noise = 0.f,  bool noTassellation=true);
        void end();

        #if defined(KINECT)
        void generatedMesh(ofxKinect &kinect, int _dist=1100, int _dist2=1200);
        void drawDebug();
        void kinectMesh();
        #endif // KINECT
};
#endif
