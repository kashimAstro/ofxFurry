#pragma once
#include "ofMain.h"
#include "ofxGui.h"
#define KINECT_MODE
#include "ofxKinect.h"
#include "ofxFurry.h"

class ofApp : public ofBaseApp{
 public:
   ofEasyCam cam;
   ofxFurry furry;
   ofxKinect kinect;
   bool guiHide;
      
   ofxPanel gui;
   ofParameter<ofVec3f> translate;
   ofParameter<bool> wireframe;
   ofParameter<float> hair;
   ofParameter<float> timer;
   ofParameter<ofVec3f> color;
   ofParameter<bool> mod;
   ofParameter<int> dist;
   ofParameter<int> dist2;
   ofParameter<int> steps;
   ofParameter<int> types;
   ofParameter<int> pol;
   
   void exit();
   void setup();
   void update();
   void draw();
   void resolutionIco(int & val);
   void keyPressed(int key);
};
