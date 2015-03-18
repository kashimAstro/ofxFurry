#include "ofMain.h"
#include "ofxDelaunay.h"
#include "ofxKinect.h"

#define STRINGIFY(A) #A

class ofxFurry : public ofBaseApp {

	public:

        int colorAlpha;
        ofVboMesh convertedMesh;
        ofxDelaunay del;
        ofImage blob;
        float noiseAmount;
        int pointSkip;
        int distnect;

        float alpha;
        float hairLeng;
        ofVec3f color;
        ofShader shader;

        void initfurry(int _pointSkip = 6, int _dist=1100 );
        void begin(ofEasyCam cam, ofVec3f color, float hairLeng = 2.2, float alpha = 1.f, float noise = 0.f,  bool noTassellation=true);
        void end();

        void generatedMesh(ofxKinect &kinect);
        void drawDebug();
        void kinectMesh();
};
