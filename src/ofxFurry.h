#pragma once
#include "ofMain.h"
#include "glsl.h"
//#ifdef KINECT_MODE
//        #pragma message("KINECT_MODE=ACTIVED")
	#include "ofxKinect.h"
	#include "THKinect.h"
//#endif

class ofxFurry : public ofBaseApp{
 public:
   ofShader shader;
   THKinect tkinect;
   glsl glslContext;
   int dist1,dist2;
   void setSteps(int steps);
   void setDistance1(int dist);
   void setDistance2(int dist2);
   void kinectMesh(int i);   
   void setupKinect(int _dist1=1100, int _dist2=1200);
   void update(ofxKinect *kinect);

   void setup();

   void exit();
   void begin(ofEasyCam cam, float hairLeng=0.5, ofVec3f translate=ofVec3f(0,0,0), float time=ofGetElapsedTimef(), ofVec3f color=ofVec3f(0.2,0.3,0.9),int types=1);
   void end();
};
