#include "ofMain.h"
#include "ofxFurry.h"
#include "ofxKinect.h"

class ofApp : public ofBaseApp{
        public:

        ofxFurry furry;
        ofEasyCam cam;
	ofxKinect kinect;

        void setup();
        void update();
        void draw();
        void keyPressed(int key);
	void exit();
};
