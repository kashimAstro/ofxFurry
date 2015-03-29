#include "ofMain.h"
#include "ofxKinect.h"
#include "ofxFurry.h"
#include "ofxGui.h"

#define KINECT
class ofApp : public ofBaseApp{
        public:

        ofxFurry furry;
        ofEasyCam cam;
        ofxKinect kinect;
	ofxPanel gui;
        ofParameter<ofVec3f> translate;
        ofParameter<ofVec3f> color;
        ofParameter<float> alpha;
        ofParameter<float> hairLeng;
        ofParameter<bool> noise;
        ofParameter<bool> tassellation;
        ofParameter<int> distnect;
        ofParameter<bool> debug;

        void setup();
        void update();
        void draw();
        void keyPressed(int key);
        void exit();
};
