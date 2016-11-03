#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxFurry.h"
#include "ofxAssimpModelLoader.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		FurryPrimitive furryprimitive;
                ofVboMesh mesh,meshWire;
                ofEasyCam camera;
                ofImage texture;
                ofxPanel gui;
                ofParameter<ofVec3f> scale;
                ofParameter<ofVec3f> direction;
                ofParameter<int> rangeorien;
                ofParameter<int> rangescale;
                ofParameter<bool> wirefill,stopNoise;
		ofxAssimpModelLoader model;
};
